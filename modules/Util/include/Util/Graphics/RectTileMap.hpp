#pragma once


#include <Util/Types.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include <cstdint>


namespace util::graphics
{

using TileID = std::uint_fast32_t;

class RectTileMap : public sf::Drawable, public sf::Transformable
{
public: // Constructors.

        RectTileMap(const sf::Vector2u size = {0, 0},
                    const sf::Vector2f tileSize = {0, 0},
                    const sf::Vector2u tileIconSize = {0, 0},
                    sf::Texture* const texture = nullptr,
                    const TileID fill = 0)
        : size(size)
        , tileSize(tileSize)
        , tileIconSize(tileIconSize)
        , vertices(sf::Quads)
        , texture(texture)
        {
                this->setSize(size);
                this->placeVertices();
                this->fill(fill);
        }

        RectTileMap(const Matrix<TileID>& tiles,
                    const sf::Vector2f tileSize = {0, 0},
                    const sf::Vector2u tileIconSize = {0, 0},
                    sf::Texture* const texture = nullptr)
        : RectTileMap(sf::Vector2u(tiles.size(), tiles.size() ? tiles[0].size() : 0),
                      tileSize, tileIconSize, texture)
        {
                this->setMap(tiles);
        }

        RectTileMap(const RectTileMap& other)
        : size        (other.size)
        , tileSize    (other.tileSize)
        , tileIconSize(other.tileIconSize)
        , tiles       (other.tiles)
        , vertices    (other.vertices)
        , texture     (other.texture)
        {
        }

        RectTileMap(RectTileMap&& other)
        : size        (std::move(other.size))
        , tileSize    (std::move(other.tileSize))
        , tileIconSize(std::move(other.tileIconSize))
        , tiles       (std::move(other.tiles))
        , vertices    (std::move(other.vertices))
        , texture     (std::move(other.texture))
        {
        }

public: // Mutators.

        void fill(const TileID fill)
        {
                this->fillArea(fill, {{}, size});
        }

        void fillArea(const TileID fill, const sf::UintRect area)
        {
                for (std::uint32_t x = area.left; x < area.width; ++x)
                for (std::uint32_t y = area.top; y < area.height; ++y)
                {
                        this->setTile({x, y}, fill);
                }
        }

        void setTile(const sf::Vector2u pos, const TileID iconIndex)
        {
                this->tiles[pos.y][pos.x] = iconIndex;

                const std::size_t vertex = 4 * (pos.x + pos.y * this->size.x);

                const auto iconSize = sf::Vector2f(this->tileIconSize);
                const std::size_t texWidth = this->texture->getSize().x;
                const sf::Vector2f texCoords = {
                        iconIndex % (texWidth / this->tileIconSize.x) * iconSize.x,
                        iconIndex / (texWidth / this->tileIconSize.x) * iconSize.y,
                };

                const sf::Vector2f topLeft     = {0,          0};
                const sf::Vector2f topRight    = {iconSize.x, 0};
                const sf::Vector2f bottomRight = {iconSize.x, iconSize.y};
                const sf::Vector2f bottomLeft  = {0,          iconSize.y};

                this->vertices[vertex + 0].texCoords = texCoords + topLeft;
                this->vertices[vertex + 1].texCoords = texCoords + topRight;
                this->vertices[vertex + 2].texCoords = texCoords + bottomRight;
                this->vertices[vertex + 3].texCoords = texCoords + bottomLeft;
        }

        void setMap(const Matrix<TileID>& tiles)
        {
                this->tiles = tiles;
                this->size.y = tiles.size();
                this->size.x = this->size.y ? tiles[0].size() : 0;

                this->placeVertices();

                for (std::uint32_t x = 0; x < this->size.x; ++x)
                for (std::uint32_t y = 0; y < this->size.y; ++y)
                {
                        this->setTile({x, y}, tiles[y][x]);
                }
        }

        void setSize(const sf::Vector2u size)
        {
                this->size = size;

                this->tiles.resize(size.y);
                for (auto& row : this->tiles)
                {
                        row.resize(size.x);
                }
        }

        void setTexture(sf::Texture* const texture)
        {
                this->texture = texture;
        }

        void setTileSize(const sf::Vector2f tileSize)
        {
                this->tileSize = tileSize;
        }

        void setTileIconSize(const sf::Vector2u tileIconSize)
        {
                this->tileIconSize = tileIconSize;
        }

public: // Accessors.

        sf::Texture* getTexture() const
        {
                return this->texture;
        }

        TileID getTile(const sf::Vector2u pos) const
        {
                return this->tiles[pos.y][pos.x];
        }

        TileID getTile(const std::size_t row, const std::size_t col) const
        {
                return this->tiles[col][row];
        }

        sf::Vector2u getSize() const
        {
                return this->size;
        }
        
        sf::Vector2f getTileSize() const
        {
                return this->tileSize;
        }
        
        sf::Vector2u getTileIconSize() const
        {
                return this->tileIconSize;
        }

        sf::FloatRect getGlobalBounds() const
        {
                return {
                        this->getPosition(),
                        {this->size.x * this->tileSize.x,
                         this->size.y * this->tileSize.y}
                };
        }

        sf::FloatRect getLocalBounds() const
        {
                return {
                        0.f, 0.f,
                        this->size.x * this->tileSize.x,
                        this->size.y * this->tileSize.y
                };
        }

public: // Overloaded operators.

        RectTileMap& operator=(const RectTileMap& other)
        {
                this->size         = other.size;
                this->tileSize     = other.tileSize;
                this->tileIconSize = other.tileIconSize;
                this->tiles        = other.tiles;
                this->vertices     = other.vertices;
                this->texture      = other.texture;
                return *this;
        }

        RectTileMap& operator=(RectTileMap&& other)
        {
                this->size         = std::move(other.size);
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
                this->vertices.resize(4 * this->size.x * this->size.y);

                // Vertices of a tile.
                const sf::Vector2f topLeft     = {0,                0};
                const sf::Vector2f topRight    = {this->tileSize.x, 0};
                const sf::Vector2f bottomRight = {this->tileSize.x, this->tileSize.y};
                const sf::Vector2f bottomLeft  = {0,                this->tileSize.y};

                for (std::size_t x = 0; x < this->size.x; ++x)
                for (std::size_t y = 0; y < this->size.y; ++y)
                {
                        const std::size_t firstVertex = 4 * (x + y * this->size.x);
                        const sf::Vector2f position = {
                                x * this->tileSize.x,
                                y * this->tileSize.y,
                        };
                        this->vertices[firstVertex + 0].position = position + topLeft;
                        this->vertices[firstVertex + 1].position = position + topRight;
                        this->vertices[firstVertex + 2].position = position + bottomRight;
                        this->vertices[firstVertex + 3].position = position + bottomLeft;
                }
        }

private: // Fields.

        sf::Vector2u size;
        sf::Vector2f tileSize;
        sf::Vector2u tileIconSize;

        Matrix<TileID> tiles;
        sf::VertexArray vertices;
        sf::Texture* texture;
};

}