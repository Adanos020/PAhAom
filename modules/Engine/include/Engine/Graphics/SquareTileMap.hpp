#pragma once


#include <Util/Types.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>


namespace engine::graphics
{

class SquareTileMap : public sf::Drawable, public sf::Transformable
{
public: // Constructors.

        SquareTileMap(size_t columns, size_t rows, float tileSize, size_t tileIconSize,
                      const util::TileID fill = 0)
        : columns(columns)
        , rows(rows)
        , tileSize(tileSize)
        , tileIconSize(tileIconSize)
        , vertices(sf::Quads)
        {
                this->tiles.resize(columns);
                std::for_each(
                        this->tiles.begin(), this->tiles.end(),
                        [=](auto& row) { row.resize(rows); }
                );

                this->placeVertices();
                this->fillArea({
                        0u, 0u,
                        static_cast<unsigned>(this->columns),
                        static_cast<unsigned>(this->rows)
                }, fill);
        }

        SquareTileMap(const util::Matrix<util::TileID>& tiles, float tileSize, size_t tileIconSize)
        : SquareTileMap(tiles.size(), tiles.size() ? tiles[0].size() : 0, tileSize, tileIconSize)
        {
                this->setMap(tiles);
        }

        SquareTileMap(SquareTileMap& other)
        : columns     (other.columns)
        , rows        (other.rows)
        , tileSize    (other.tileSize)
        , tileIconSize(other.tileIconSize)
        , tiles       (other.tiles)
        , vertices    (other.vertices)
        , texture     (other.texture)
        {
        }

        SquareTileMap(SquareTileMap&& other)
        : columns     (std::move(other.columns))
        , rows        (std::move(other.rows))
        , tileSize    (std::move(other.tileSize))
        , tileIconSize(std::move(other.tileIconSize))
        , tiles       (std::move(other.tiles))
        , vertices    (std::move(other.vertices))
        , texture     (std::move(other.texture))
        {
        }

public: // Mutators.

        void fillArea(sf::UintRect area, util::TileID fill)
        {
                for (unsigned x = area.left; x < area.width; ++x)
                for (unsigned y = area.top; y < area.height; ++y)
                {
                        this->setTile({x, y}, fill);
                }
        }

        void setTexture(sf::Texture* const texture)
        {
                this->texture = texture;
        }

        void setTile(const sf::Vector2u pos, const util::TileID iconIndex)
        {
                this->tiles[pos.x][pos.y] = iconIndex;

                const size_t vertex = 4 * (pos.x + pos.y * this->columns);

                const float iconSize = this->tileIconSize;
                const size_t texWidth = this->texture->getSize().x;
                const sf::Vector2f texCoords = {
                        iconIndex % (texWidth / this->tileIconSize) * iconSize,
                        iconIndex / (texWidth / this->tileIconSize) * iconSize,
                };

                const sf::Vector2f topLeft     = {0,        0};
                const sf::Vector2f topRight    = {iconSize, 0};
                const sf::Vector2f bottomRight = {iconSize, iconSize};
                const sf::Vector2f bottomLeft  = {0,        iconSize};

                this->vertices[vertex + 0].texCoords = texCoords + topLeft;
                this->vertices[vertex + 1].texCoords = texCoords + topRight;
                this->vertices[vertex + 2].texCoords = texCoords + bottomRight;
                this->vertices[vertex + 3].texCoords = texCoords + bottomLeft;
        }

        void setMap(const util::Matrix<util::TileID>& tiles)
        {
                this->tiles = tiles;
                this->columns = tiles.size();
                this->rows = this->columns ? tiles[0].size() : 0;

                this->placeVertices();

                for (unsigned x = 0; x < this->columns; ++x)
                for (unsigned y = 0; y < this->rows; ++y)
                {
                        this->setTile({x, y}, tiles[x][y]);
                }
        }

public: // Accessors.

        sf::Texture* getTexture() const
        {
                return this->texture;
        }

        util::TileID getTile(const sf::Vector2u pos) const
        {
                return this->tiles[pos.x][pos.y];
        }

        size_t getColumns() const
        {
                return this->columns;
        }

        size_t getRows() const
        {
                return this->rows;
        }
        
        size_t getTileSize() const
        {
                return this->tileSize;
        }
        
        size_t getTileIconSize() const
        {
                return this->tileIconSize;
        }

public: // Overloaded operators.

        SquareTileMap& operator=(const SquareTileMap& other)
        {
                this->columns      = other.columns;
                this->rows         = other.rows;
                this->tileSize     = other.tileSize;
                this->tileIconSize = other.tileIconSize;
                this->tiles        = other.tiles;
                this->vertices     = other.vertices;
                this->texture      = other.texture;
                return *this;
        }

        SquareTileMap& operator=(SquareTileMap&& other)
        {
                this->columns      = std::move(other.columns);
                this->rows         = std::move(other.rows);
                this->tileSize     = std::move(other.tileSize);
                this->tileIconSize = std::move(other.tileIconSize);
                this->tiles        = std::move(other.tiles);
                this->vertices     = std::move(other.vertices);
                this->texture      = std::move(other.texture);
                return *this;
        }

public: // Derived interface.

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
        {
                states.transform *= this->getTransform();
                states.texture = this->texture;
                target.draw(vertices, states);
        }

private: // Helper functions.

        void placeVertices()
        {
                this->vertices.resize(4 * this->columns * this->rows);

                const sf::Vector2f topLeft     = {0,              0};
                const sf::Vector2f topRight    = {this->tileSize, 0};
                const sf::Vector2f bottomRight = {this->tileSize, this->tileSize};
                const sf::Vector2f bottomLeft  = {0,              this->tileSize};

                for (size_t x = 0; x < this->columns; ++x)
                for (size_t y = 0; y < this->rows; ++y)
                {
                        const size_t tile = 4 * (x + y * this->columns);
                        const sf::Vector2f position = {x * this->tileSize, y * this->tileSize};

                        this->vertices[tile + 0].position = position + topLeft;
                        this->vertices[tile + 1].position = position + topRight;
                        this->vertices[tile + 2].position = position + bottomRight;
                        this->vertices[tile + 3].position = position + bottomLeft;
                }
        }

private: // Fields.

        size_t columns;
        size_t rows;

        float tileSize;
        size_t tileIconSize;

        util::Matrix<util::TileID> tiles;
        sf::VertexArray vertices;
        sf::Texture* texture;
};

}