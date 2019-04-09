Game = {
    drawables = {
        {
            type = "rect tile map",
            tiles = {},
            tileSize = 16,
            tileIconSize = 16,
            texture = "tileset",
            origin = "center",
            position = {
                x = Settings.video.resolution.x / 2,
                y = Settings.video.resolution.y / 2,
            },
        }
    }
}

function Game:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    self.drawables[1].tiles = generate_dungeon {x = 37, y = 21}
    return o
end

function Game:handle_input(event)
    if event.type == "KeyPressed" then
        local kc = event.code
        if kc == Keyboard.Escape then
            pop_state()
        end
    end
end

function Game:update(dt)
end

function Game:draw()
    return self.drawables
end