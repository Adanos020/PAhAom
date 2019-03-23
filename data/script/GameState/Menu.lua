Menu = {
    text = {
        type = "sfText",
        content = "Menu, press Enter to continue,\nEsc to exit.",
        font = "unifont",
    }
}

function Menu:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self

    self.text.position = {
        x = Settings.Video.Resolution.x / 2,
        y = Settings.Video.Resolution.y / 2,
    }

    return o
end

function Menu:handle_input(event)
    if event.type == Event.KeyPressed then
        local kc = event.key.code
        if kc == Keyboard.Return then
            broadcast { type = "PushState", state = "Game"}
        elseif kc == Keyboard.Escape then
            broadcast { type = "PopState"}
        end
    end
end

function Menu:update(dt)

end

function Menu:draw()
    return self.text
end