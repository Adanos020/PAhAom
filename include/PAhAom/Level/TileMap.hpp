#pragma once


#include <util/Types.hpp>

#include <SFML/System/Vector2.hpp>

#include <fstream>


namespace PAhAom::Level
{

enum class Tile : util::TileID
{
        VOID,
        FLOOR,
        WALL,
};


template<size_t rows, size_t cols>
class TileMap
{
public:

        TileMap<rows, cols>(const Tile fill = Tile::VOID);

        Tile* operator[](size_t row);
        Tile* operator[](size_t row) const;

        std::ifstream& loadFromFile(std::ifstream& file);

        void fillArea(const sf::UintRect area, Tile);

private:

        Tile tiles[rows][cols];
};

constexpr static const size_t MAP_WIDTH = 39;
constexpr static const size_t MAP_HEIGHT = 21;

}