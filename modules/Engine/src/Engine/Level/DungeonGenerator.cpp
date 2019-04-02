#include <Engine/Level/Generator.hpp>

#include <Util/Random.hpp>
#include <Util/Ranges.hpp>
#include <Util/Types.hpp>

#include <SFML/Graphics/Rect.hpp>


namespace engine::level
{

using Neighbours = int;
using Room = sf::UintRect;

template<size_t width, size_t height>
TileMap<width, height> DungeonGenerator<width, height>::generate()
{
        this->tileMap = TileMap<width, height>(Tile::WALL);

        this->generateMaze();
        util::FastVector<Room> rooms = this->spreadRooms();
        this->removeDeadEnds();
        this->reduceCorridors(rooms);

        return std::move(this->tileMap);
}

template<size_t width, size_t height>
void DungeonGenerator<width, height>::generateMaze()
{
        util::FastVector<sf::Vector2u> cells;
        cells.reserve((width - 2) / 2 * (height - 2) / 2);

        // Picking a random cell with odd coordinates.
        cells += {
                util::Random::uniform(0u, unsigned(width  - 1)) | 1,
                util::Random::uniform(0u, unsigned(height - 1)) | 1
        };
        this->tileMap[cells.back().x][cells.back().y] = Tile::CORRIDOR;

        sf::Vector2i currentDirection = directions[pickNeighbour(cells.back(), Tile::WALL)];

        while (!cells.empty())
        {
                const sf::Vector2u currentCell = cells.back();
                Neighbours neighbours = findNeighbours(currentCell, Tile::WALL);

                // If there are no more adjacent cells to occupy, go back.
                if (!neighbours)
                {
                        cells.pop_back();
                        continue;
                }

                // Advance to the next cell according to current direction.
                auto nextCell = sf::Vector2u(sf::Vector2i(currentCell) + currentDirection);

                // Decide on whether make a turn.
                if (nextCell.x >= width - 1 or nextCell.y >= height - 1 or
                    this->tileMap[nextCell.x][nextCell.y] == Tile::CORRIDOR or
                    util::Random::chance(0.1))
                {
                        currentDirection = directions[pickNeighbour(neighbours)];
                        nextCell = sf::Vector2u(sf::Vector2i(currentCell) + currentDirection);
                }

                const auto onWay = sf::Vector2u(sf::Vector2i(currentCell) + currentDirection / 2);

                this->tileMap[onWay.x][onWay.y] = Tile::CORRIDOR;
                this->tileMap[nextCell.x][nextCell.y] = Tile::CORRIDOR;

                cells += nextCell;
        }
}

template<size_t width, size_t height>
Neighbours DungeonGenerator<width, height>::findNeighbours(const sf::Vector2u cell, const Tile tile,
                                                           const size_t distance) const
{
        // Setting all relevant bits corresponding to the neighbouring wall blocks.
        return LEFT   * int(cell.x > distance - 1      and tileMap[cell.x - distance][cell.y] == tile)
             | RIGHT  * int(cell.x < width - distance  and tileMap[cell.x + distance][cell.y] == tile)
             | TOP    * int(cell.y > distance - 1      and tileMap[cell.x][cell.y - distance] == tile)
             | BOTTOM * int(cell.y < height - distance and tileMap[cell.x][cell.y + distance] == tile)
        ;
}

template<size_t width, size_t height>
Neighbours DungeonGenerator<width, height>::pickNeighbour(const Neighbours neighbours)
{
        static util::FastVector<Neighbours> all = { TOP, BOTTOM, LEFT, RIGHT };
        util::FastVector<Neighbours> existing;

        // Picking out the neighbour bits as separate numbers.
        std::copy_if(all.begin(), all.end(), existing.begin(),
                [=](const Neighbours n) { return bool(neighbours & n); });

        return util::Random::oneOf(existing.begin(), existing.end());
}

template<size_t width, size_t height>
Neighbours DungeonGenerator<width, height>::pickNeighbour(const sf::Vector2u cell, const Tile tile) const
{
        return pickNeighbour(findNeighbours(cell, tile));
}

template<size_t width, size_t height>
util::FastVector<Room> DungeonGenerator<width, height>::spreadRooms()
{
        util::FastVector<Room> rooms;
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
                const Room newRoom = { position, size };

                // Avoid intersections.
                if (std::none_of(rooms.begin(), rooms.end(),
                        [&](const Room& room) { return room.intersects(newRoom); }))
                {
                        rooms += newRoom;
                }
        }

        rooms.shrink_to_fit();

        // Putting the rooms on the map.
        for (Room& room : rooms)
        {
                tileMap.fillArea(room, Tile::ROOM);
        }

        return rooms;
}

template<size_t width, size_t height>
void DungeonGenerator<width, height>::removeDeadEnds()
{
        util::FastVector<sf::Vector2u> deadEnds;

        // Searching for dead ends.
        for (unsigned int x = 1; x < width;  x += 2)
        for (unsigned int y = 1; y < height; y += 2)
        {
                sf::Vector2u cell = { x, y };
                if (isDeadEnd(cell))
                {
                        deadEnds += cell;
                }
        }

        // Filling all dead ends with walls.
        for (sf::Vector2u cell : deadEnds)
        {
                while (isDeadEnd(cell))
                {
                        sf::Vector2i direction = directions[findNeighbours(cell, Tile::CORRIDOR, 1)];
                        sf::Vector2u onWay = sf::Vector2u(sf::Vector2i(cell) + direction / 2);

                        this->tileMap[cell.x][cell.y]   = Tile::WALL;
                        this->tileMap[onWay.x][onWay.y] = Tile::WALL;

                        cell = sf::Vector2u(sf::Vector2i(cell) + direction);
                }
        }
}

template<size_t width, size_t height>
bool DungeonGenerator<width, height>::isDeadEnd(sf::Vector2u cell) const
{
        return this->tileMap[cell.x][cell.y] == Tile::CORRIDOR and countCloseNeighbours(cell, Tile::WALL) == 3;
}

template<size_t width, size_t height>
size_t DungeonGenerator<width, height>::countNeighbours(const Neighbours neighbours)
{
        // Summing all relevant bits.
        return ((neighbours >> 0) & 1)
             + ((neighbours >> 1) & 1)
             + ((neighbours >> 2) & 1)
             + ((neighbours >> 3) & 1)
        ;
}

template<size_t width, size_t height>
size_t DungeonGenerator<width, height>::countCloseNeighbours(const sf::Vector2u cell, const Tile tile) const
{
        return countNeighbours(findNeighbours(cell, tile, 1));
}

template<size_t width, size_t height>
void DungeonGenerator<width, height>::reduceCorridors([[maybe_unused]] const util::FastVector<Room>& rooms)
{
        // TODO: finish implementation
}

template<size_t width, size_t height>
void DungeonGenerator<width, height>::fillCorridor(const sf::Vector2u at)
{
        util::FastVector<sf::Vector2u> cells;
        cells += at;

        while (not cells.empty())
        {
                Neighbours neighbours = findNeighbours(at, Tile::CORRIDOR, 1);
                if (not neighbours)
                {
                        cells.pop_back();
                        continue;
                }

                util::FastVector<Neighbours> corridorNeighbours =
                        extractNeighbours(neighbours);

                util::FastVector<sf::Vector2i> directions;
                std::transform(corridorNeighbours.begin(), corridorNeighbours.end(), directions.begin(),
                        [this](const Neighbours n) { return this->directions[n]; });

                // TODO: finish implementation
        }
}

template<size_t width, size_t height>
util::FastVector<Neighbours> DungeonGenerator<width, height>::extractNeighbours(const Neighbours neighbours)
{
        static util::FastVector<Neighbours> all = { TOP, BOTTOM, LEFT, RIGHT };
        util::FastVector<Neighbours> existing;

        // Picking out the neighbour bits as separate numbers.
        std::copy_if(all.begin(), all.end(), existing.begin(),
                [=](Neighbours n) { return bool(neighbours & n); });

        return existing;
}

template class DungeonGenerator<MAP_WIDTH, MAP_HEIGHT>;

}