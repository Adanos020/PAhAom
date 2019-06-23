local mapSize      -- vector
local tiles        -- matrix of numbers
local rooms        -- array of rects
local mapArea      -- rectangle
local maxRoomSize  -- vector
local minRoomSize  = vec(3, 3)
local maxRoomTries = 100

local Tile = {
    VOID    = 0,
    FLOOR   = 1,
    WALL    = 7,
    HALLWAY = 17,
}

local Neighbours = {
    LEFT  = 1 << 0,
    RIGHT = 1 << 1,
    UP    = 1 << 2,
    DOWN  = 1 << 3,
}

local directions = {
    vec(-2,  0), -- LEFT
    vec( 2,  0), -- RIGHT
    vec( 0, -2), -- UP
    vec( 0,  2), -- DOWN
}

local function fillArea(area, tile)
    assert(math.isRectangle(area))
    assert(math.type(tile) == "integer")

    for x = area.position.x, area.position.x + area.size.x - 1 do
        for y = area.position.y, area.position.y + area.size.y - 1 do
            tiles[y][x] = tile
        end
    end
end

local function initMap()
    tiles = {}
    for row = 1, mapSize.y do
        tiles[row] = {}
    end
    fillArea({position = vec(1, 1), size = mapSize}, Tile.WALL)
end

local function leftIs(pos, tile, distance)
    return pos.x > distance and tiles[pos.y][pos.x - distance] == tile
end

local function rightIs(pos, tile, distance)
    return pos.x <= mapSize.x - distance and tiles[pos.y][pos.x + distance] == tile
end

local function upIs(pos, tile, distance)
    return pos.y > distance and tiles[pos.y - distance][pos.x] == tile
end

local function downIs(pos, tile, distance)
    return pos.y <= mapSize.y - distance and tiles[pos.y + distance][pos.x] == tile
end

local function findNeighbours(pos, tile, distance)
    return (leftIs (pos, tile, distance) and Neighbours.LEFT  or 0)
         | (rightIs(pos, tile, distance) and Neighbours.RIGHT or 0)
         | (upIs   (pos, tile, distance) and Neighbours.UP    or 0)
         | (downIs (pos, tile, distance) and Neighbours.DOWN  or 0)
end

local function countNeighbours(neighbours)
    assert(math.type(neighbours) == "integer")
    return ((neighbours >> 0) & 1)
         + ((neighbours >> 1) & 1)
         + ((neighbours >> 2) & 1)
         + ((neighbours >> 3) & 1)
end

local function countCloseNeighbours(pos, tile)
    assert(math.type(tile) == "integer")
    return countNeighbours(findNeighbours(pos, tile, 1))
end

local function neighboursIndices(neighbours)
    assert(math.type(neighbours) == "integer")
    local indices = {}
    for i = 0, 3 do
        if ((neighbours >> i) & 1) == 1 then
            table.insert(indices, i + 1)
        end
    end
    return indices, #indices
end

local function pickDirection(neighbours)
    if neighbours then
        assert(math.type(neighbours) == "integer")
        local inds, n = neighboursIndices(neighbours)
        return directions[inds[random.uniform(1, n)]]
    end
    return directions[random.uniform(1, #directions)]
end

local function generateMaze()
    local cells = {
        -- Pick a random first cell with odd coordinates.
        vec(~1 & random.uniform(2, mapSize.x),
            ~1 & random.uniform(2, mapSize.y))
    }

    local currCell = cells[#cells]
    tiles[currCell.y][currCell.x] = Tile.HALLWAY

    while #cells > 0 do
        currCell = cells[#cells]
        local neighbours = findNeighbours(currCell, Tile.WALL, 2)
        local currDir = pickDirection(neighbours)

        -- If there are no more adjacent cells to occupy, go back.
        if neighbours == 0 then
            table.remove(cells)
        else
            -- Advance to the next cell in current direction.
            local nextCell = vector.add(currCell, currDir)

            -- Decide on whether make a turn.
            while not math.rectangleContains(mapArea, nextCell)
                or tiles[nextCell.y][nextCell.x] == Tile.HALLWAY
                or random.chance(0.1)
            do
                currDir = pickDirection(neighbours)
                nextCell = vector.add(currCell, currDir)
            end

            -- Carve the corridor.
            local midWay = vector.add(currCell, vector.divide(currDir, 2))
            tiles[midWay.y][midWay.x] = Tile.HALLWAY
            tiles[nextCell.y][nextCell.x] = Tile.HALLWAY
            table.insert(cells, nextCell)
        end
    end
end

local function spreadRooms()
    rooms = {}
    for i = 1, maxRoomTries do
        local roomSize = vec(
            1 | random.uniform(minRoomSize.x, math.tointeger(maxRoomSize.x)),
            1 | random.uniform(minRoomSize.y, math.tointeger(maxRoomSize.y)))
        local roomPos = vec(
            ~1 & random.uniform(2, mapSize.x - roomSize.x),
            ~1 & random.uniform(2, mapSize.y - roomSize.y))

        local newRoom = {position = roomPos, size = roomSize}

        if table.none(rooms,
            function(room)
                return math.rectangleIntersects(room, newRoom)
            end)
        then
            table.insert(rooms, newRoom)
        end
    end

    for _, room in ipairs(rooms) do
        fillArea(room, Tile.FLOOR)
    end
end

local function isDeadEnd(pos)
    return tiles[pos.y][pos.x] == Tile.HALLWAY
       and countCloseNeighbours(pos, Tile.WALL) == 3
end

local function removeDeadEnds()
    -- Search for dead ends.
    local deadEnds = {}
    for x = 2, mapSize.x, 2 do
        for y = 2, mapSize.y, 2 do
            local cell = vec(x, y)
            if isDeadEnd(cell) then
                table.insert(deadEnds, cell)
            end
        end
    end

    -- Fill all dead ends with walls.
    for _, c in ipairs(deadEnds) do
        local cell = c
        while isDeadEnd(cell) do
            local neighbours = findNeighbours(cell, Tile.HALLWAY, 1)
            local dir = directions[neighboursIndices(neighbours)[1]]
            local midWay = vec(cell.x + dir.x // 2, cell.y + dir.y // 2)

            tiles[cell.y][cell.x] = Tile.WALL
            tiles[midWay.y][midWay.x] = Tile.WALL

            cell = vector.add(cell, dir)
        end
    end
end

function generateDungeon(size)
    assert(isVector(size))

    mapSize = vec(
        math.tointeger(size.x),
        math.tointeger(size.y))
    mapArea = {
        position = vec(1, 1),
        size = mapSize,
    }
    maxRoomSize = vec(
        math.clamp(mapSize.x // 2, 3, 13),
        math.clamp(mapSize.y // 2, 3, 13))

    initMap()
    generateMaze()
    spreadRooms()
    removeDeadEnds()

    return tiles
end