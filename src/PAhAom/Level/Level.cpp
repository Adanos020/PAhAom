#include <PAhAom/Level/Level.hpp>

#include <fstream>


namespace PAhAom::Level
{

template<size_t width, size_t height>
Level<width, height>::Level()
{

}

template<size_t width, size_t height>
Level<width, height>::Level(Generator<width, height>& gen)
{
        this->map.setMap(gen.generate());
}

template<size_t width, size_t height>
Level<width, height>::Level(std::string_view path)
{
        std::ifstream file(path.data());
        TileMap<width, height> loadedMap;
        if (!loadedMap.loadFromFile(file))
        {
                // throw exception
        }
        this->map.setMap(loadedMap);
}

template<size_t width, size_t height>
void Level<width, height>::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
        states.transform *= this->getTransform();
        target.draw(this->map, states);
}

template class Level<MAP_WIDTH, MAP_HEIGHT>;

}