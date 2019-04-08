local width          -- number
local height         -- number
local tiles          -- table
local rooms          -- table
local max_room_tries -- number

function generate_dungeon(size)
    width, height = size.x, size.y
    generate_maze()
    spread_rooms()
    remove_dead_ends()
    return tiles
end

local function generate_maze()

end

local function spread_rooms()
    for i = 1, max_room_tries do
        
    end
end

local function remove_dead_ends()
    
end