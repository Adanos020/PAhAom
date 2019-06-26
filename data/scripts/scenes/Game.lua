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
        textureRect = rectangle(0, 0, 16, 16),
        z = 1,
    },
    rigidBody = {
        velocity = vector(0, 0),
    },
    input = {
        onKeyPressed = function(self, key)
            local velocity = self.rigidBody.velocity
            if key == Keyboard.Left then
                velocity.x = -200
            elseif key == Keyboard.Right then
                velocity.x = 200
            elseif key == Keyboard.Up then
                velocity.y = -200
            elseif key == Keyboard.Down then
                velocity.y = 200
            end
            entity.setVelocity(self, velocity)
        end,
        onKeyReleased = function(self, key)
            local velocity = self.rigidBody.velocity
            if key == Keyboard.Left or key == Keyboard.Right then
                velocity.x = 0
            elseif key == Keyboard.Up or key == Keyboard.Down then
                velocity.y = 0
            end
            entity.setVelocity(self, velocity)
        end,
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
        game.switchTo("Menu")
    end
end

function Game:update(dt)
    -- print(level.position.x, level.position.y, "|",
    --       player.position.x, player.position.y)
end