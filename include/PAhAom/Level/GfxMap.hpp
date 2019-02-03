#pragma once


#include <PAhAom/Level/TileMap.hpp>

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

        GfxMap<width, height>();
        GfxMap<width, height>(const TileMap<width, height>&);

        void setTile(const sf::Vector2u pos, const Tile);
        void setMap(const TileMap<width, height>&);

public:

        virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;

private:

        void placeVertices();

private:

        sf::VertexArray tileMap;
        sf::Texture* tileSet;

        inline static const unsigned int tileSize = 16;
        inline static const unsigned int tileIconSize = 16;
        inline static const size_t idToIconIndex[] = {
                0, // VOID
                16, // FLOOR
                12, // WALL
        };
};

}