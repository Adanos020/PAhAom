local elapsed = 0

local windowCenter = math.vectorDivide(Settings.video.resolution, 2)

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

function Menu:onKeyPressed(key)
    if key == Keyboard.Enter then
        pushScene "Game"
    elseif key == Keyboard.Escape then
        popScene()
    end
end

function Menu:update(dt)
    elapsed = elapsed + dt
    
    local sinel = math.sin(elapsed)
    local polar = math.vectorFromPolar(100, elapsed)

    setPosition(greeting, math.vectorAdd(windowCenter, polar))
    setRotation(greeting, sinel * 30)
    setScale(greeting, math.vector(
        sinel * sinel + 0.5,
        sinel * sinel + 0.5
    ))
end