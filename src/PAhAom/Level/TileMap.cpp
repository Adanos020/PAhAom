#include <PAhAom/Level/TileMap.hpp>

#include <algorithm>


namespace PAhAom::Level
{

template<size_t rows, size_t cols>
TileMap<rows, cols>::TileMap(const Tile fill)
{
        std::fill_n(*this->tiles, rows * cols, fill);
}

template<size_t rows, size_t cols>
Tile* TileMap<rows, cols>::operator[](size_t row)
{
        return this->tiles[row];
}

template<size_t rows, size_t cols>
Tile* TileMap<rows, cols>::operator[](size_t row) const
{
        return const_cast<Tile* const>(this->tiles[row]);
}

template<size_t rows, size_t cols>
std::ifstream& TileMap<rows, cols>::loadFromFile(std::ifstream& file)
{
        return file;
}

template<size_t rows, size_t cols>
void TileMap<rows, cols>::fillArea(const sf::UintRect area, Tile tile)
{
        for (size_t col = area.left; col < area.left + area.width; ++col)
        {
                std::fill_n(&this->tiles[col][area.top], area.height, tile);
        }
}

template class TileMap<MAP_WIDTH, MAP_HEIGHT>;

}