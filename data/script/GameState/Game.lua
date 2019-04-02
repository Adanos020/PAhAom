Game = {
    drawables = {
        currentLevel = { type = "Level" },
    },
}

function Game:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

function Game:handle_input(event)
    if event.type == "KeyPressed" then
        local kc = event.code
        if kc == Keyboard.Escape then
            broadcast { type = "PopState" }
        end
    end
end

function Game:update(dt)
end

function Game:draw()
end