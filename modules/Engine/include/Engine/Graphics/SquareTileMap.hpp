#pragma once


#include <Engine/Resources.hpp>

#include <Util/Types.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>


namespace engine::graphics
{

class SquareTileMap : public sf::Drawable, public sf::Transformable
{
public: // Interface.

        SquareTileMap(size_t columns, size_t rows, size_t tileSize, size_t tileIconSize)
        : columns(columns), rows(rows)
        , tileSize(tileSize), tileIconSize(tileIconSize)
        , vertices(sf::Quads, 4 * this->columns * this->rows)
        {
                this->tiles.resize(columns);
                std::for_each(
                        this->tiles.begin(),
                        this->tiles.end(),
                        [=](auto& row) { row.resize(rows); }
                );
                this->placeVertices();
        }

        SquareTileMap(size_t columns, size_t rows, const util::TileID fill, size_t tileSize, size_t tileIconSize)
        : SquareTileMap(columns, rows, tileSize, tileIconSize)
        {
                for (unsigned x = 0; x < this->columns; ++x)
                for (unsigned y = 0; y < this->rows; ++y)
                {
                        this->setTile({x, y}, fill);
                }
        }

        SquareTileMap(const util::Matrix<util::TileID>& tiles, size_t tileSize, size_t tileIconSize)
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

        void setTexture(sf::Texture* const texture)
        {
                this->texture = texture;
        }

        void setTile(const sf::Vector2u pos, const util::TileID iconIndex)
        {
                const size_t vertex = 4 * (pos.x + pos.y * this->columns);

                const size_t texWidth = this->texture->getSize().x;
                const sf::Vector2f texCoords = {
                        this->tileIconSize * float(iconIndex % (texWidth / this->tileIconSize)),
                        this->tileIconSize * float(iconIndex / (texWidth / this->tileIconSize))
                };

                const sf::Vector2f topLeft     = { 0,                         0 };
                const sf::Vector2f topRight    = { float(this->tileIconSize), 0 };
                const sf::Vector2f bottomRight = { float(this->tileIconSize), float(this->tileIconSize) };
                const sf::Vector2f bottomLeft  = { 0,                         float(this->tileIconSize) };

                this->vertices[vertex + 0].texCoords = texCoords + topLeft;
                this->vertices[vertex + 1].texCoords = texCoords + topRight;
                this->vertices[vertex + 2].texCoords = texCoords + bottomRight;
                this->vertices[vertex + 3].texCoords = texCoords + bottomLeft;
        }

        util::TileID getTile(const sf::Vector2u pos) const
        {
                return this->tiles[pos.x][pos.y];
        }

        void setMap(const util::Matrix<util::TileID>& tiles)
        {
                this->tiles = tiles;
                this->columns = tiles.size();
                this->rows = this->columns ? tiles[0].size() : 0;

                for (unsigned x = 0; x < this->columns; ++x)
                for (unsigned y = 0; y < this->rows; ++y)
                {
                        this->setTile({x, y}, tiles[x][y]);
                }
        }

        void fillArea(sf::UintRect area, util::TileID fill)
        {
                for (unsigned x = area.left; x < area.width; ++x)
                for (unsigned y = area.top; y < area.height; ++y)
                {
                        this->setTile({x, y}, fill);
                }
        }

public: // Accessors.

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

        util::FastVector<util::TileID>& operator[](size_t col)
        {
                return this->tiles[col];
        }

        util::FastVector<util::TileID>& operator[](size_t col) const
        {
                return const_cast<util::FastVector<util::TileID>&>(this->tiles[col]);
        }

        SquareTileMap& operator=(SquareTileMap& other)
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
                const sf::Vector2f topLeft     = { 0,                     0 };
                const sf::Vector2f topRight    = { float(this->tileSize), 0 };
                const sf::Vector2f bottomRight = { float(this->tileSize), float(this->tileSize) };
                const sf::Vector2f bottomLeft  = { 0,                     float(this->tileSize) };

                for (size_t x = 0; x < this->columns; ++x)
                for (size_t y = 0; y < this->rows; ++y)
                {
                        const size_t tile = 4 * (x + y * this->columns);
                        const sf::Vector2f position = {
                                float(x * this->tileSize),
                                float(y * this->tileSize)
                        };

                        this->vertices[tile + 0].position = position + topLeft;
                        this->vertices[tile + 1].position = position + topRight;
                        this->vertices[tile + 2].position = position + bottomRight;
                        this->vertices[tile + 3].position = position + bottomLeft;
                }
        }

private: // Fields.

        size_t columns;
        size_t rows;

        size_t tileSize;
        size_t tileIconSize;

        util::Matrix<util::TileID> tiles;
        sf::VertexArray vertices;
        sf::Texture* texture;
};

}