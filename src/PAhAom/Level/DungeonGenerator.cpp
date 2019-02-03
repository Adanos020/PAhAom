#include <PAhAom/Level/Generator.hpp>

#include <util/Random.hpp>
#include <util/Ranges.hpp>
#include <util/Types.hpp>

#include <SFML/Graphics/Rect.hpp>


namespace PAhAom::Level
{

using Neighbours = int;

template<size_t width, size_t height>
DungeonGenerator<width, height>::DungeonGenerator()
: tileMap(Tile::WALL)
{

}

template<size_t width, size_t height>
TileMap<width, height> DungeonGenerator<width, height>::generate()
{
        this->generateMaze();
        util::FastVector<sf::UintRect> rooms = this->spreadRooms();
        this->removeDeadEnds();
        this->reduceCorridors(rooms);
        return this->tileMap;
}

template<size_t width, size_t height>
void DungeonGenerator<width, height>::generateMaze()
{
        util::FastVector<sf::Vector2u> cells;
        cells.reserve((width - 2) / 2 * (height - 2) / 2);
        cells += {
                util::Random::uniform(0u, unsigned(width  - 1)) | 1,
                util::Random::uniform(0u, unsigned(height - 1)) | 1
        };

        this->tileMap[cells.back().x][cells.back().y] = Tile::FLOOR;

        sf::Vector2i currentDirection = directions[pickNeighbour(cells.back())];

        while (!cells.empty())
        {
                const sf::Vector2u currentCell = cells.back();
                Neighbours neighbours = findNeighbours(currentCell);
                if (!neighbours)
                {
                        cells.pop_back();
                        continue;
                }

                sf::Vector2u nextCell = { currentCell.x + currentDirection.x,
                                          currentCell.y + currentDirection.y };

                if (nextCell.x >= width - 1 || nextCell.y >= height - 1
                        || this->tileMap[nextCell.x][nextCell.y] == Tile::FLOOR
                        || util::Random::chance(0.1))
                {
                        currentDirection = directions[pickNeighbour(neighbours)];
                        nextCell = { currentCell.x + currentDirection.x,
                                     currentCell.y + currentDirection.y };
                }

                const sf::Vector2u onWay = { currentCell.x + currentDirection.x / 2,
                                             currentCell.y + currentDirection.y / 2 };

                this->tileMap[onWay.x][onWay.y] = Tile::FLOOR;
                this->tileMap[nextCell.x][nextCell.y] = Tile::FLOOR;

                cells += nextCell;
        }
}

template<size_t width, size_t height>
util::FastVector<sf::UintRect> DungeonGenerator<width, height>::spreadRooms()
{
        util::FastVector<sf::UintRect> rooms;
        rooms.reserve(MAX_ROOMS);

        // Generating random rooms.
        for (size_t i = 0; i < MAX_ROOM_TRIES; ++i)
        {
                const sf::Vector2u size = {
                        util::Random::uniform(MIN_ROOM_SIZE.x, MAX_ROOM_SIZE.x) | 1,
                        util::Random::uniform(MIN_ROOM_SIZE.y, MAX_ROOM_SIZE.y) | 1
                };
                const sf::Vector2u position = {
                        util::Random::uniform(1u, unsigned(width  - size.x - 1)) | 1,
                        util::Random::uniform(1u, unsigned(height - size.y - 1)) | 1
                };
                const sf::UintRect newRoom = { position, size };

                if (std::none_of(rooms.begin(), rooms.end(),
                        [&](sf::UintRect& room) { return room.intersects(newRoom); }))
                {
                        rooms += newRoom;
                }
        }

        rooms.shrink_to_fit();

        // Putting the rooms on the map.
        for (sf::UintRect& room : rooms)
        {
                tileMap.fillArea(room, Tile::FLOOR);
        }

        return std::move(rooms);
}

template<size_t width, size_t height>
void DungeonGenerator<width, height>::removeDeadEnds()
{
        util::FastVector<sf::Vector2u> deadEnds;

        // Searching for dead ends.
        for (unsigned int x = 1; x < width;  x += 2)
        for (unsigned int y = 1; y < height; y += 2)
        {
                if (isDeadEnd({ x, y }))
                {
                        deadEnds += { x, y };
                }
        }

        // Filling all dead ends with walls.
        for (sf::Vector2u cell : deadEnds)
        {
                while (isDeadEnd(cell))
                {
                        // We can assume each cell in `deadEnds` to have exactly 1 neighbour.
                        sf::Vector2i direction = directions[0b1111 & ~findNeighbours(cell, 1)];
                        sf::Vector2u onWay = { cell.x + direction.x / 2, cell.y + direction.y / 2 };

                        this->tileMap[cell.x][cell.y] = Tile::WALL;
                        this->tileMap[onWay.x][onWay.y] = Tile::WALL;

                        cell = { cell.x + direction.x, cell.y + direction.y };
                }
        }
}

template<size_t width, size_t height>
void DungeonGenerator<width, height>::reduceCorridors(const util::FastVector<sf::UintRect>& rooms)
{

}

template<size_t width, size_t height>
Neighbours DungeonGenerator<width, height>::findNeighbours(const sf::Vector2u cell, const size_t distance) const
{
        return LEFT   * int(cell.x > distance - 1      && tileMap[cell.x - distance][cell.y] == Tile::WALL)
             | RIGHT  * int(cell.x < width - distance  && tileMap[cell.x + distance][cell.y] == Tile::WALL)
             | TOP    * int(cell.y > distance - 1      && tileMap[cell.x][cell.y - distance] == Tile::WALL)
             | BOTTOM * int(cell.y < height - distance && tileMap[cell.x][cell.y + distance] == Tile::WALL)
        ;
}

template<size_t width, size_t height>
Neighbours DungeonGenerator<width, height>::pickNeighbour(const Neighbours neighbours)
{
        static util::FastVector<Neighbours> all = { 1 << 0, 1 << 1, 1 << 2, 1 << 3 };
        util::FastVector<Neighbours> existing;

        std::copy_if(all.begin(), all.end(), existing.begin(),
                [=](Neighbours n) { return bool(neighbours & n); });

        return util::Random::oneOf(existing.begin(), existing.end());
}

template<size_t width, size_t height>
Neighbours DungeonGenerator<width, height>::pickNeighbour(const sf::Vector2u cell) const
{
        return pickNeighbour(findNeighbours(cell));
}

template<size_t width, size_t height>
size_t DungeonGenerator<width, height>::countNeighbours(const Neighbours neighbours)
{
        return ((neighbours >> 0) & 1)
             + ((neighbours >> 1) & 1)
             + ((neighbours >> 2) & 1)
             + ((neighbours >> 3) & 1)
        ;
}

template<size_t width, size_t height>
size_t DungeonGenerator<width, height>::countCloseNeighbours(const sf::Vector2u cell) const
{
        return countNeighbours(findNeighbours(cell, 1));
}

template<size_t width, size_t height>
bool DungeonGenerator<width, height>::isDeadEnd(sf::Vector2u cell) const
{
        return this->tileMap[cell.x][cell.y] == Tile::FLOOR && countCloseNeighbours(cell) == 3;
}

template class DungeonGenerator<MAP_WIDTH, MAP_HEIGHT>;

}