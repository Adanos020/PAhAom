local windowCenter = vec.divide(Settings.video.resolution, 2)

local elapsedTime = 0

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
    position = vector(0, 0),
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

function Menu:newBall(pos, radius, color, velocity)
    local ball = {
        position = pos,
        graphics = {
            type = "circle",
            radius = radius,
            fillColor = color,
            origin = "center",
            z = 2,
        },
        rigidBody = {
            velocity = velocity,
            mass = radius / 10,
        }
    }
    table.insert(self.entities, ball)
    return ball
end

function Menu:onKeyPressed(key)
    if key == Keyboard.Enter then
        game.switchTo("Game")
    elseif key == Keyboard.Escape then
        game.quit()
    elseif key == Keyboard.Space then
        entity.add(self:newBall(
            vector(random.uniform(0, Settings.video.resolution.x),
                   random.uniform(0, Settings.video.resolution.y)),
            random.uniform(10, 25),
            rgb(random.uniform(0, 256),
                random.uniform(0, 256),
                random.uniform(0, 256)),
            vector(random.uniform(-20, 20), random.uniform(-20, 20))
        ))
    end
end

function Menu:update(dt)
    elapsedTime = elapsedTime + dt

    local sinel = math.sin(elapsedTime)
    local polar = vec.fromPolar(100, elapsedTime)

    entity.setPosition(greeting, vec.add(windowCenter, polar))
    entity.setRotation(greeting, sinel * 30)
    entity.setScale(greeting, sinel * sinel + 0.5)
end