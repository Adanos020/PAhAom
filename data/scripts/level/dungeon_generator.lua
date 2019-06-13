local map_size      -- vector
local tiles         -- matrix of numbers
local rooms         -- array of rects
local map_area      -- rectangle
local max_room_size -- vector
local min_room_size  = math.vector(3, 3)
local max_room_tries = 100

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
    math.vector(-2,  0), -- LEFT
    math.vector( 2,  0), -- RIGHT
    math.vector( 0, -2), -- UP
    math.vector( 0,  2), -- DOWN
}

local function fill_area(area, tile)
    assert(math.is_rectangle(area))
    assert(math.type(tile) == "integer")

    for x = area.position.x, area.position.x + area.size.x - 1 do
        for y = area.position.y, area.position.y + area.size.y - 1 do
            tiles[y][x] = tile
        end
    end
end

local function init_map()
    tiles = {}
    for row = 1, map_size.y do
        tiles[row] = {}
    end
    fill_area({position = math.vector(1, 1), size = map_size}, Tile.WALL)
end

local function left_is(pos, tile, distance)
    return pos.x > distance and tiles[pos.y][pos.x - distance] == tile
end

local function right_is(pos, tile, distance)
    return pos.x <= map_size.x - distance and tiles[pos.y][pos.x + distance] == tile
end

local function up_is(pos, tile, distance)
    return pos.y > distance and tiles[pos.y - distance][pos.x] == tile
end

local function down_is(pos, tile, distance)
    return pos.y <= map_size.y - distance and tiles[pos.y + distance][pos.x] == tile
end

local function find_neighbours(pos, tile, distance)
    return (left_is (pos, tile, distance) and Neighbours.LEFT  or 0)
         | (right_is(pos, tile, distance) and Neighbours.RIGHT or 0)
         | (up_is   (pos, tile, distance) and Neighbours.UP    or 0)
         | (down_is (pos, tile, distance) and Neighbours.DOWN  or 0)
end

local function count_neighbours(neighbours)
    assert(math.type(neighbours) == "integer")

    return ((neighbours >> 0) & 1)
         + ((neighbours >> 1) & 1)
         + ((neighbours >> 2) & 1)
         + ((neighbours >> 3) & 1)
end

local function count_close_neighbours(pos, tile)
    assert(math.is_vector(pos))
    assert(math.type(tile) == "integer")

    return count_neighbours(find_neighbours(pos, tile, 1))
end

local function neighbours_indices(neighbours)
    assert(math.type(neighbours) == "integer")

    local indices = {}
    for i = 0, 3 do
        if ((neighbours >> i) & 1) == 1 then
            table.insert(indices, i + 1)
        end
    end
    return indices, #indices
end

local function pick_direction(neighbours)
    if neighbours then
        assert(math.type(neighbours) == "integer")
        local inds, n = neighbours_indices(neighbours)
        return directions[inds[random.uniform(1, n)]]
    end

    return directions[random.uniform(1, #directions)]
end

local function generate_maze()
    local cells = {
        math.vector( -- Picking a random first cell with odd coordinates.
            ~1 & random.uniform(2, map_size.x),
            ~1 & random.uniform(2, map_size.y))
    }

    local curr_cell = cells[#cells]
    tiles[curr_cell.y][curr_cell.x] = Tile.HALLWAY
    
    while #cells > 0 do
        curr_cell = cells[#cells]
        local neighbours = find_neighbours(curr_cell, Tile.WALL, 2)
        local curr_dir = pick_direction(neighbours)

        -- If there are no more adjacent cells to occupy, go back.
        if neighbours == 0 then
            table.remove(cells)
        else
            -- Advance to the next cell in current direction.
            local next_cell = math.vector(
                curr_cell.x + curr_dir.x,
                curr_cell.y + curr_dir.y)

            -- Decide on whether make a turn.
            while not math.rectangle_contains(map_area, next_cell)
                or tiles[next_cell.y][next_cell.x] == Tile.HALLWAY
                or random.chance(0.1)
            do
                curr_dir = pick_direction(neighbours)
                next_cell = math.vector(
                    curr_cell.x + curr_dir.x,
                    curr_cell.y + curr_dir.y)
            end

            -- Carve the corridor.
            local mid_way = math.vector(
                curr_cell.x + curr_dir.x // 2,
                curr_cell.y + curr_dir.y // 2)
            tiles[mid_way.y][mid_way.x] = Tile.HALLWAY
            tiles[next_cell.y][next_cell.x] = Tile.HALLWAY
            table.insert(cells, next_cell)
        end
    end
end

local function spread_rooms()
    rooms = {}
    for i = 1, max_room_tries do
        local room_size = math.vector(
            1 | random.uniform(min_room_size.x, max_room_size.x),
            1 | random.uniform(min_room_size.y, max_room_size.y))
        local room_pos = math.vector(
            ~1 & random.uniform(2, map_size.x - room_size.x),
            ~1 & random.uniform(2, map_size.y - room_size.y))

        local new_room = {position = room_pos, size = room_size}

        if table.none(rooms,
            function(room)
                return math.rectangle_intersects(room, new_room)
            end)
        then
            table.insert(rooms, new_room)
        end
    end

    for _, room in ipairs(rooms) do
        fill_area(room, Tile.FLOOR)
    end
end

local function is_dead_end(pos)
    assert(math.is_vector(pos))

    return tiles[pos.y][pos.x] == Tile.HALLWAY
       and count_close_neighbours(pos, Tile.WALL) == 3
end

local function remove_dead_ends()
    -- Searching for dead ends.
    local dead_ends = {}
    for x = 2, map_size.x, 2 do
        for y = 2, map_size.y, 2 do
            local cell = math.vector(x, y)
            if is_dead_end(cell) then
                table.insert(dead_ends, cell)
            end
        end
    end

    -- Filling all dead ends with walls.
    for _, c in ipairs(dead_ends) do
        local cell = c
        while is_dead_end(cell) do
            local neighbours = find_neighbours(cell, Tile.HALLWAY, 1)
            local dir = directions[neighbours_indices(neighbours)[1]]
            local mid_way = math.vector(cell.x + dir.x // 2, cell.y + dir.y // 2)

            tiles[cell.y][cell.x] = Tile.WALL
            tiles[mid_way.y][mid_way.x] = Tile.WALL
            
            cell = math.vector(cell.x + dir.x, cell.y + dir.y)
        end
    end
end

function generate_dungeon(size)
    assert(math.is_vector(size), "Size must be a vector.")

    map_size = math.vector(
        math.tointeger(size.x),
        math.tointeger(size.y))
    map_area = {
        position = math.vector(1, 1),
        size = map_size,
    }
    max_room_size = math.vector(
        math.clamp(map_size.x // 2, 3, 13),
        math.clamp(map_size.y // 2, 3, 13))

    init_map()
    generate_maze()
    spread_rooms()
    remove_dead_ends()

    return tiles
end