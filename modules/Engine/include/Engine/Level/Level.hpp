#pragma once


#include <Engine/Level/Generator.hpp>
#include <Engine/Level/GfxMap.hpp>
#include <Engine/Level/TileMap.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transformable.hpp>


namespace engine::level
{

template<size_t width, size_t height>
class Level : public sf::Drawable, public sf::Transformable
{
public:

        Level<width, height>() = default;

        Level<width, height>(Generator<width, height>& gen)
        {
                this->tiles = gen.generate();
                this->map.setMap(this->tiles);
        }

        Level<width, height>(std::string_view path)
        {
                std::ifstream file(path.data());
                TileMap<width, height> loadedMap;
                if (not loadedMap.loadFromFile(file))
                {
                        // throw exception
                }
                this->map.setMap(loadedMap);
        }

public:

        virtual auto draw(sf::RenderTarget& target, sf::RenderStates states) const override -> void
        {
                states.transform *= this->getTransform();
                target.draw(this->map, states);
        }

private:

        TileMap<width, height> tiles;
        GfxMap<width, height> map;
};

}