Game = {
    currentLevel = { type = "Level" }
}

function Game:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

function Game:handle_input(event)
    if event.type == Event.KeyPressed then
        local kc = event.key.code
        if kc == Keyboard.Escape then
            broadcast { type = "PopState" }
        end
    end
end

function Game:update(dt)

end

function Game:draw()
    return currentLevel
end