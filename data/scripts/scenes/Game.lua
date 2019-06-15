local windowCenter = math.vectorDivide(Settings.video.resolution, 2)

local level = {
    position = windowCenter,
    graphics = {
        type = "rect tile map",
        tiles = {},
        tileSize = 16,
        tileIconSize = 16,
        texture = "tileset",
        origin = "center",
    },
}

Game = {
    entities = {level, }
}

function Game:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    level.graphics.tiles = generateDungeon(math.vector(37, 21))
    return o
end

function Game:onKeyPressed(key)
    if key == Keyboard.Escape then
        popScene()
    end
end

function Game:update(dt)
end