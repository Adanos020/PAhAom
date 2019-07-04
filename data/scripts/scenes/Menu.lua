local windowCenter = settings.video.resolution:divide(2)

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
    position = vec.new(0, 0),
    graphics = {
        type = "rectangle",
        texture = "menu bkg",
        size = settings.video.resolution,
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
    if key == keyboard.enter then
        game.switchTo("Game")
    elseif key == keyboard.escape then
        game.quit()
    end
end

function Menu:onMousePressed(button, x, y)
    if button == mouse.left then
        entity.add(self:newBall(
            vec.new(x, y),
            random.uniform(10, 25),
            rgb(random.uniform(0, 256),
                random.uniform(0, 256),
                random.uniform(0, 256)),
            vec.new(random.uniform(-20, 20), random.uniform(-20, 20))
        ))
    end
end

function Menu:update(dt)
    elapsedTime = elapsedTime + dt

    local sinel = math.sin(elapsedTime)
    local polar = vec.fromPolar(100, elapsedTime)

    entity.setPosition(greeting, vec.new(windowCenter):add(polar))
    entity.setRotation(greeting, sinel * 30)
    entity.setScale(greeting, sinel * sinel + 0.5)
end