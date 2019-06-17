local elapsedTime = 0

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
        type = "rectangle",
        texture = "menu bkg",
        size = Settings.video.resolution,
        z = 0,
    },
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

function Menu:newCircle(pos, radius, color)
    local circle = {
        position = pos,
        graphics = {
            type = "circle",
            radius = radius,
            fillColor = color,
            origin = "center",
            z = 2,
        },
    }
    table.insert(self.entities, circle)
    return circle
end

function Menu:onKeyPressed(key)
    if key == Keyboard.Enter then
        pushScene "Game"
    elseif key == Keyboard.Escape then
        popScene()
    elseif key == Keyboard.Space then
        addEntity(self:newCircle(
            math.vector(
                random.uniform(0, Settings.video.resolution.x),
                random.uniform(0, Settings.video.resolution.y)
            ),
            random.uniform(10, 25),
            {
                r = random.uniform(0, 255),
                g = random.uniform(0, 255),
                b = random.uniform(0, 255),
            }
        ))
    end
end

function Menu:update(dt)
    elapsedTime = elapsedTime + dt

    local sinel = math.sin(elapsedTime)
    local polar = math.vectorFromPolar(100, elapsedTime)

    setPosition(greeting, math.vectorAdd(windowCenter, polar))
    setRotation(greeting, sinel * 30)
    setScale(greeting, sinel * sinel + 0.5)

    for i = 3, #self.entities do

    end
end