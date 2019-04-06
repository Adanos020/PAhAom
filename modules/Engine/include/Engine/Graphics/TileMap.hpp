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

class TileMap : public sf::Drawable, public sf::Transformable
{
public: // Methods.

        TileMap(size_t width, size_t height, size_t tileSize, size_t tileIconSize)
        : width(width), height(height)
        , tileSize(tileSize), tileIconSize(tileIconSize)
        , vertices(sf::Quads, 4 * this->width * this->height)
        {
                this->tiles.resize(width);
                std::for_each(
                        this->tiles.begin(),
                        this->tiles.end(),
                        [=](auto& row) { row.resize(height); }
                );
                this->placeVertices();
        }

        TileMap(size_t width, size_t height, const util::TileID fill, size_t tileSize, size_t tileIconSize)
        : TileMap(width, height, tileSize, tileIconSize)
        {
                for (unsigned x = 0; x < this->width; ++x)
                for (unsigned y = 0; y < this->height; ++y)
                {
                        this->setTile({x, y}, fill);
                }
        }

        TileMap(const util::Matrix<util::TileID>& tiles, size_t tileSize, size_t tileIconSize)
        : TileMap(tiles.size(), tiles[0].size(), tileSize, tileIconSize)
        {
                this->setMap(tiles);
        }

        void setTexture(sf::Texture* const texture)
        {
                this->texture = texture;
        }

        void setTile(const sf::Vector2u pos, const util::IconIndex iconIndex)
        {
                const size_t vertex = 4 * (pos.x + pos.y * this->width);

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

        void setMap(const util::Matrix<util::TileID>& tiles)
        {
                this->tiles = tiles;

                for (unsigned x = 0; x < this->width; ++x)
                for (unsigned y = 0; y < this->height; ++y)
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

        util::FastVector<util::TileID>& operator[](size_t col)
        {
                return this->tiles[col];
        }

        util::FastVector<util::TileID>& operator[](size_t col) const
        {
                return const_cast<util::FastVector<util::TileID>&>(this->tiles[col]);
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

                for (size_t x = 0; x < this->width; ++x)
                for (size_t y = 0; y < this->height; ++y)
                {
                        const size_t tile = 4 * (x + y * this->width);
                        const sf::Vector2f position = { float(x * this->tileSize), float(y * this->tileSize) };

                        this->vertices[tile + 0].position = position + topLeft;
                        this->vertices[tile + 1].position = position + topRight;
                        this->vertices[tile + 2].position = position + bottomRight;
                        this->vertices[tile + 3].position = position + bottomLeft;
                }
        }

public: // Constants.

        const size_t width;
        const size_t height;

        const size_t tileSize;
        const size_t tileIconSize;

private: // Fields.

        util::Matrix<util::TileID> tiles;
        sf::VertexArray vertices;
        sf::Texture* texture;
};

}