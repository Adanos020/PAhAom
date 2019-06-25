local windowCenter = vec.divide(Settings.video.resolution, 2)

local level = {
    position = windowCenter,
    graphics = {
        type = "rect tile map",
        tiles = {},
        tileSize = 16,
        tileIconSize = 16,
        texture = "tileset",
        origin = "center",
        z = 0,
    },
}

local player = {
    position = windowCenter,
    graphics = {
        type = "sprite",
        texture = "player",
        textureRect = {
            left = 0,
            right = 0,
            width = 16,
            height = 16,
        },
        z = 1,
    },
    rectRB = {
        size = vector(16, 16),
        velocity = vector(0, 0)
    },
    input = {
        onKeyPressed = function(self, key)
            if key == Keyboard.Left then
                self.rectRB.velocity.x = -30
            elseif key == Keyboard.Right then
                self.rectRB.velocity.x = 30
            elseif key == Keyboard.Up then
                self.rectRB.velocity.y = -30
            elseif key == Keyboard.Down then
                self.rectRB.velocity.y = 30
            end
        end,
        onKeyReleased = function(self, key)
            if key == Keyboard.Left or key == Keyboard.Right then
                self.rectRB.velocity.x = 0
            elseif key == Keyboard.Up or key == Keyboard.Down then
                self.rectRB.velocity.y = 0
            end
        end
    },
}

Game = {
    entities = {level, player, }
}

function Game:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    level.graphics.tiles = generateDungeon(vector(37, 21))
    return o
end

function Game:onKeyPressed(key)
    if key == Keyboard.Escape then
        scene.switchTo "Menu"
    end
end

function Game:update(dt)
    entity.moveBy(player, vec.multiply(player.rectRB.velocity, dt))
end