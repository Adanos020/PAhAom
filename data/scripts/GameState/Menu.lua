Menu = {
    drawables = {
        {
            type = "text",
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
            type = "circle shape",
            fillColor = "green",
            radius = 30,
            position = {x = 140, y = 40}
        },
        {
            type = "rectangle shape",
            fillColor = "blue",
            size = {x = 69, y = 42},
            position = {
                x = Settings.video.resolution.x - 80,
                y = Settings.video.resolution.y - 50
            }
        },
        {
            type = "sprite",
            texture = "tileset",
            textureRect = {
                left = 0, top = 16,
                width = 16, height = 16
            },
            scale = 4,
            position = {x = 10, y = 10}
        }
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