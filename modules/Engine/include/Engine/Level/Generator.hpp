#pragma once


#include <Engine/Level/TileMap.hpp>

#include <algorithm>


namespace engine::level
{

template<size_t width, size_t height>
class Generator
{
public:
        virtual TileMap<width, height> generate() = 0;
};


template<size_t width, size_t height>
class DungeonGenerator : public Generator<width, height>
{
        static_assert(width & height & 1, "Both map's dimensions must be odd.");
        static_assert(width >= 5 and height >= 5, "Both map's dimensions must be no less than 5.");

        using Neighbours = int;
        using Room = sf::UintRect;

public: // Interface methods.

        virtual TileMap<width, height> generate() override;

private: // Helper methods.

        void generateMaze();
        Neighbours findNeighbours(const sf::Vector2u cell, const Tile, const size_t distance = 2) const;
        Neighbours pickNeighbour(const sf::Vector2u cell, const Tile) const;
        static Neighbours pickNeighbour(const Neighbours);

        util::FastVector<Room> spreadRooms();

        void removeDeadEnds();
        bool isDeadEnd(const sf::Vector2u cell) const;
        size_t countCloseNeighbours(const sf::Vector2u cell, const Tile tile) const;
        static size_t countNeighbours(const Neighbours);

        void reduceCorridors(const util::FastVector<Room>& rooms);
        void fillCorridor(const sf::Vector2u at);
        static util::FastVector<Neighbours> extractNeighbours(const Neighbours);


private: // Fields.

        TileMap<width, height> tileMap;

private: // Static data.

        constexpr inline static const Neighbours
                NONE   = 0,
                TOP    = 1 << 0,
                BOTTOM = 1 << 1,
                LEFT   = 1 << 2,
                RIGHT  = 1 << 3
        ;

        inline static const sf::Vector2i directions[] = {
                {  0,  0 }, // NONE
                {  0, -2 }, // UP
                {  0,  2 }, // DOWN
                {  0,  0 }, // DOWN UP
                { -2,  0 }, // LEFT
                { -2, -2 }, // LEFT UP
                { -2,  2 }, // LEFT DOWN
                { -2,  0 }, // LEFT DOWN UP
                {  2,  0 }, // RIGHT
                {  2, -2 }, // RIGHT UP
                {  2,  2 }, // RIGHT DOWN
                {  2,  0 }, // RIGHT DOWN UP
                {  0,  0 }, // RIGHT LEFT
                {  0, -2 }, // RIGHT LEFT UP
                {  0,  2 }, // RIGHT LEFT DOWN
                {  0,  0 }, // RIGHT LEFT DOWN UP
        };

        inline static const sf::Vector2u MIN_ROOM_SIZE = { 3, 3 };
        inline static const sf::Vector2u MAX_ROOM_SIZE = { std::clamp(11ul, 3ul, width  / 2),
                                                           std::clamp(11ul, 3ul, height / 2) };

        constexpr inline static const size_t MIN_ROOMS = std::clamp(5ul, 1ul, std::min(width - 2, height - 2) / 3);
        constexpr inline static const size_t MAX_ROOMS = ((width - 2) / 3) * ((height - 2) / 3) / 4;

        constexpr inline static const size_t MAX_ROOM_TRIES = 1000;
};

}