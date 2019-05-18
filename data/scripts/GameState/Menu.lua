Menu = {
    entities = {
        {
            position = {
                x = Settings.video.resolution.x / 2,
                y = Settings.video.resolution.y / 2,
            },
            graphics2D = {
                type = "text",
                content = "Menu, press Enter to continue,\nEsc to exit.",
                font = "unifont",
                fillColor = "yellow",
                origin = "center"
            },
        },
    }
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
            push_state "Game"
        elseif kc == Keyboard.Escape then
            pop_state()
        end
    end
end

function Menu:update(dt)
end

function Menu:draw()
    return self.entities
end