Menu = {
    drawables = {
        {
            type = "sfText",
            content = "Menu, press Enter to continue,\nEsc to exit.",
            font = "unifont",
            position = {
                x = Settings.video.resolution.x / 2,
                y = Settings.video.resolution.y / 2,
            },
            fillColor = "yellow",
            origin = "center"
        },
        {
            type = "sfCircleShape",
            fillColor = "yellow",
            radius = 30,
            position = { 40, 140 }
        },
        -- {
        --     type = "sfRectangleShape",
        --     fillColor = "blue",
        --     size = { 69, 42 },
        --     position = {
        --         Settings.video.resolution.x - 80,
        --         Settings.video.resolution.y - 50
        --     }
        -- },
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
    return self.drawables
end