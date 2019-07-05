local windowCenter = vec.new(settings.video.resolution:divide(2))

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
        textureRect = irect.new(0, 0, 16, 16),
        z = 1,
    },
    rigidBody = {
        velocity = vec.new(0, 0),
    },
    input = {
        onKeyPressed = function(me, key)
            local velocity = me.rigidBody.velocity
            if key == keyboard.left then
                velocity.x = -200
            elseif key == keyboard.right then
                velocity.x = 200
            elseif key == keyboard.up then
                velocity.y = -200
            elseif key == keyboard.down then
                velocity.y = 200
            end
            entity.setVelocity(me, velocity)
        end,
        onKeyReleased = function(me, key)
            local velocity = me.rigidBody.velocity
            if key == keyboard.left then
                velocity.x = keyboard.isPressed(keyboard.right) and  200 or 0
            elseif key == keyboard.right then
                velocity.x = keyboard.isPressed(keyboard.left)  and -200 or 0
            elseif key == keyboard.up then
                velocity.y = keyboard.isPressed(keyboard.down)  and  200 or 0
            elseif key == keyboard.down then
                velocity.y = keyboard.isPressed(keyboard.up)    and -200 or 0
            end
            entity.setVelocity(me, velocity)
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
    level.graphics.tiles = generateDungeon(ivec.new(37, 21))
    return o
end

function Game:onKeyPressed(key)
    if key == keyboard.escape then
        game.switchTo("Menu")
    end
end

function Game:update(dt)
    -- print(level.position.x, level.position.y, "|",
    --       player.position.x, player.position.y)
end