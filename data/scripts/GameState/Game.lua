Game = {
    drawables = {
        {
            type = "sfText",
            content = "Game, press Esc to exit.",
            font = "unifont",
            position = {
                x = Settings.video.resolution.x / 2,
                y = Settings.video.resolution.y / 2,
            },
            fillColor = "red",
            origin = "center"
        }
    }
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
            pop_state()
        end
    end
end

function Game:update(dt)
end

function Game:draw()
    return self.drawables
end