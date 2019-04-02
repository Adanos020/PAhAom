Menu = {
    drawables = {
        {
            type = "sfText",
            content = "Menu, press Enter to continue,\nEsc to exit.",
            font = "unifont",
            position = {
                -- x = Settings.Video.resolution.x / 2,
                -- y = Settings.Video.resolution.y / 2,
                0, 0
            },
            fillColor = "yellow",
            centeredOrigin = true
        },
    },
}

function Menu:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

function Menu:handle_input(event)
    if event.type == "KeyPressed" then
        local kc = event.code
        if kc == Keyboard.Enter then
            broadcast { type = "PushState", state = "Game" }
        elseif kc == Keyboard.Escape then
            broadcast { type = "PopState"}
        end
    end
end

function Menu:update(dt)
end

function Menu:draw()
    return self.drawables
end