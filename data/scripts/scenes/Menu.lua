local elapsed = 0

local window_center = math.vector(
    Settings.video.resolution.x / 2,
    Settings.video.resolution.y / 2
)

local greeting = {
    graphics = {
        type = "text",
        content = "Enter to continue, Esc to exit.",
        font = "unifont",
        fillColor = "yellow",
        origin = "center",
        z = 1,
    },
}

local bkg = {
    graphics = {
        type = "rectangle shape",
        texture = "menu bkg",
        size = Settings.video.resolution,
        z = 0,
    }
}

Menu = {
    entities = {greeting, bkg, }
}

function Menu:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

function Menu:handle_input(event)
    if key_pressed(event, Keyboard.Enter) then
        push_scene "Game"
    elseif key_pressed(event, Keyboard.Escape) then
        pop_scene()
    end
end

function Menu:update(dt)
    elapsed = elapsed + dt
    local polar = math.vector_from_polar(100, elapsed)
    set_position(greeting, math.vector_add(window_center, polar))
    set_rotation(greeting, math.sin(elapsed) * 30)
end