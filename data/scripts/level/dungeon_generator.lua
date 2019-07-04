local mapSize      -- vector
local mapArea      -- irect.new
local maxRoomSize  -- vector
local tiles        -- matrix of numbers

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
    ivec.new(-2,  0), -- LEFT
    ivec.new( 2,  0), -- RIGHT
    ivec.new( 0, -2), -- UP
    ivec.new( 0,  2), -- DOWN
}


-- Helpers

local function fillArea(area, tile)
    assert(math.type(tile) == "integer")
    for x = area.left, area.left + area.width - 1 do
        for y = area.top, area.top + area.height - 1 do
            tiles[y][x] = tile
        end
    end
end

local function findNeighbours(pos, tile, distance)
    local function leftIs(pos, tile, distance)
        return pos.x > distance
           and tiles[pos.y][pos.x - distance] == tile
    end
    local function rightIs(pos, tile, distance)
        return pos.x <= mapSize.x - distance
           and tiles[pos.y][pos.x + distance] == tile
    end
    local function upIs(pos, tile, distance)
        return pos.y > distance
           and tiles[pos.y - distance][pos.x] == tile
    end
    local function downIs(pos, tile, distance)
        return pos.y <= mapSize.y - distance
           and tiles[pos.y + distance][pos.x] == tile
    end
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
        return directions[inds[random.iuniform(1, n)]]
    end
    return directions[random.iuniform(1, #directions)]
end

local function isDeadEnd(pos)
    return tiles[pos.y][pos.x] == Tile.HALLWAY
       and countCloseNeighbours(pos, Tile.WALL) == 3
end


-- Procedures

local function initialise(size)
    mapSize = ivec.new(size)
    mapArea = irect.new(ivec.new(1, 1), mapSize)
    maxRoomSize = ivec.new(iclamp(mapSize.x // 2, 3, 13),
                           iclamp(mapSize.y // 2, 3, 13))
    tiles = {}
    for row = 1, mapSize.y do
        tiles[row] = {}
    end
    fillArea(mapArea, Tile.WALL)
end

local function generateMaze()
    local cells = {
        -- Pick a random first cell with odd coordinates.
        ivec.new(~1 & random.iuniform(2, mapSize.x),
                 ~1 & random.iuniform(2, mapSize.y))
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
            local nextCell = currCell:add(currDir)

            -- Decide on whether make a turn.
            while not mapArea:contains(nextCell)
                or tiles[nextCell.y][nextCell.x] == Tile.HALLWAY
                or random.chance(0.1)
            do
                currDir = pickDirection(neighbours)
                nextCell = currCell:add(currDir)
            end

            -- Carve the corridor.
            local midWay = currCell:add(currDir:divide(2))
            tiles[midWay.y][midWay.x] = Tile.HALLWAY
            tiles[nextCell.y][nextCell.x] = Tile.HALLWAY
            table.insert(cells, nextCell)
        end
    end
end

local function spreadRooms()
    local minRoomSize = ivec.new(3, 3)
    local maxRoomTries = 100
    local rooms = {}

    for i = 1, maxRoomTries do
        local roomSize = ivec.new(
            1 | random.iuniform(minRoomSize.x, maxRoomSize.x),
            1 | random.iuniform(minRoomSize.y, maxRoomSize.y))
        local roomPos = ivec.new(
            ~1 & random.iuniform(2, mapSize.x - roomSize.x),
            ~1 & random.iuniform(2, mapSize.y - roomSize.y))

        local newRoom = irect.new(roomPos, roomSize)
        local function overlapsNewRoom(room)
            return newRoom:intersects(room)
        end

        if noneOf(rooms, overlapsNewRoom) then
            table.insert(rooms, newRoom)
        end
    end

    -- Fill the established room areas.
    for _, room in ipairs(rooms) do
        fillArea(room, Tile.FLOOR)
    end
end

local function fillDeadEnds()
    -- Find dead ends.
    local deadEnds = {}
    for x = 2, mapSize.x, 2 do
        for y = 2, mapSize.y, 2 do
            local cell = ivec.new(x, y)
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
            local midWay = cell:add(dir:divide(2))

            tiles[cell.y][cell.x] = Tile.WALL
            tiles[midWay.y][midWay.x] = Tile.WALL

            cell = cell:add(dir)
        end
    end
end

function generateDungeon(size)
    initialise(size)
    generateMaze()
    spreadRooms()
    fillDeadEnds()
    return tiles
end