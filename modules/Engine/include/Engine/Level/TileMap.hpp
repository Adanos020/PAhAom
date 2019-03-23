#pragma once


#include <Util/Types.hpp>

#include <SFML/System/Vector2.hpp>

#include <algorithm>
#include <fstream>


namespace engine::level
{

enum class Tile : util::TileID
{
        VOID,
        ROOM,
        CORRIDOR,
        WALL,
};


template<size_t rows, size_t cols>
class TileMap
{
public:

        TileMap<rows, cols>() = default;

        TileMap<rows, cols>(const Tile fill)
        {
                std::fill_n(*this->tiles, rows * cols, fill);
        }

        Tile* operator[](size_t row)
        {
                return this->tiles[row];
        }

        Tile* operator[](size_t row) const
        {
                return const_cast<Tile* const>(this->tiles[row]);
        }

        std::ifstream& loadFromFile(std::ifstream& file)
        {
                return file;
        }

        void fillArea(const sf::UintRect area, Tile tile)
        {
                for (size_t col = area.left; col < area.left + area.width; ++col)
                {
                        std::fill_n(&this->tiles[col][area.top], area.height, tile);
                }
        }

private:

        Tile tiles[rows][cols];
};

constexpr static const size_t MAP_WIDTH  = 39;
constexpr static const size_t MAP_HEIGHT = 21;

}