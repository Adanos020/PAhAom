local elapsed = 0

local window_center = {
    x = Settings.video.resolution.x / 2,
    y = Settings.video.resolution.y / 2,
}

local greeting = {
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
    if key_pressed(event, Keyboard.Enter) then
        push_state "Game"
    elseif key_pressed(event, Keyboard.Escape) then
        pop_state()
    end
end

function Menu:update(dt)
    elapsed = elapsed + dt
    local polar = math.vector_from_polar(100, elapsed)
    set_position(greeting, math.vector_add(window_center, polar))
    set_rotation(greeting, elapsed * 20)
end