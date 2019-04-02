Game = {
    drawables = {
        {
            type = "sfText",
            content = "Game, press Esc to exit.",
            font = "unifont",
            position = {
                -- x = Settings.Video.resolution.x / 2,
                -- y = Settings.Video.resolution.y / 2,
                0, 0
            },
            fillColor = "red",
            centeredOrigin = true
        }
    },
}

function Game:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

function Game:handle_input(event)
    if event.type == "KeyPressed" then
        local kc = event.code
        if kc == Keyboard.Escape then
            broadcast { type = "PopState" }
        end
    end
end

function Game:update(dt)
end

function Game:draw()
    return self.drawables
end