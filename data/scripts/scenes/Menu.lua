local greeting = {
    position = {
        x = Settings.video.resolution.x / 2,
        y = Settings.video.resolution.y / 2,
    },
    graphics = {
        type = "text",
        content = "Menu, press Enter to continue,\nEsc to exit.",
        font = "unifont",
        fillColor = "yellow",
        origin = "center",
    },
}

Menu = {
    entities = {
        greeting
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

local elapsed = 0
function Menu:update(dt)
    elapsed = elapsed + dt
    set_position(greeting, math.vector_add(
        {
            x = Settings.video.resolution.x / 2,
            y = Settings.video.resolution.y / 2,
        },
        math.vector_from_polar(100, elapsed)))
    set_rotation(greeting, elapsed * 20)
end