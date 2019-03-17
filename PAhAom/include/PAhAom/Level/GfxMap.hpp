#pragma once


#include <PAhAom/Level/TileMap.hpp>
#include <PAhAom/Resources.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>


namespace PAhAom::Level
{

template<size_t width, size_t height>
class GfxMap : public sf::Drawable, public sf::Transformable
{
public:

        GfxMap<width, height>()
        : GfxMap(TileMap<width, height>(Tile::WALL))
        {
        }

        GfxMap<width, height>(const TileMap<width, height>& tiles)
        : tileMap(sf::Quads, 4 * width * height)
        , tileSet(Resources::get<sf::Texture>("tileset"))
        {
                this->placeVertices();
                this->setMap(tiles);
        }

        void setTile(const sf::Vector2u pos, const Tile newTile)
        {
                const size_t vertex = 4 * (pos.x + pos.y * width);
                const size_t iconIndex = idToIconIndex[int(newTile)];

                const size_t texWidth = this->tileSet->getSize().x;
                const sf::Vector2f texCoords = { tileIconSize * float(iconIndex % (texWidth / tileIconSize)),
                                                 tileIconSize * float(iconIndex / (texWidth / tileIconSize)) };

                const sf::Vector2f topLeft     = { 0,            0 };
                const sf::Vector2f topRight    = { tileIconSize, 0 };
                const sf::Vector2f bottomRight = { tileIconSize, tileIconSize };
                const sf::Vector2f bottomLeft  = { 0,            tileIconSize };

                this->tileMap[vertex + 0].texCoords = texCoords + topLeft;
                this->tileMap[vertex + 1].texCoords = texCoords + topRight;
                this->tileMap[vertex + 2].texCoords = texCoords + bottomRight;
                this->tileMap[vertex + 3].texCoords = texCoords + bottomLeft;
        }

        void setMap(const TileMap<width, height>& tiles)
        {
                for (unsigned x = 0; x <  width; ++x)
                for (unsigned y = 0; y < height; ++y)
                {
                        this->setTile({x, y}, tiles[x][y]);
                }
        }

public:

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
        {
                states.transform *= this->getTransform();
                states.texture = this->tileSet;
                target.draw(tileMap, states);
        }

private:

        void placeVertices()
        {
                const sf::Vector2f topLeft     = { 0,        0 };
                const sf::Vector2f topRight    = { tileSize, 0 };
                const sf::Vector2f bottomRight = { tileSize, tileSize };
                const sf::Vector2f bottomLeft  = { 0,        tileSize };

                for (size_t x = 0; x <  width; ++x)
                for (size_t y = 0; y < height; ++y)
                {
                        const size_t vertex = 4 * (x + y * width);
                        const sf::Vector2f position = { float(x * tileSize), float(y * tileSize) };

                        this->tileMap[vertex + 0].position = position + topLeft;
                        this->tileMap[vertex + 1].position = position + topRight;
                        this->tileMap[vertex + 2].position = position + bottomRight;
                        this->tileMap[vertex + 3].position = position + bottomLeft;
                }
        }

private:

        sf::VertexArray tileMap;
        sf::Texture* tileSet;

        inline static const unsigned int tileSize = 16;
        inline static const unsigned int tileIconSize = 16;
        inline static const size_t idToIconIndex[] = {
                0, // VOID
                16, // ROOM
                17, // CORRIDOR
                12, // WALL
        };
};

}