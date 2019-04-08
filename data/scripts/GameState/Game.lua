Game = {
    drawables = {
        {
            type = "text",
            content = "Game, press Esc to exit.",
            font = "unifont",
            position = {
                x = Settings.video.resolution.x / 2,
                y = 20,
            },
            fillColor = "red",
            origin = "center",
        },
        {
            type = "rect tile map",
            tiles = {
                {  1,  1, 16,  1,  1 },
                {  1, 16, 16, 16,  1 },
                {  1, 16, 16, 16,  1 },
                {  1, 16, 16, 16,  1 },
                { 64, 64, 64, 64, 64 },
                { 64, 64, 64, 64, 64 },
            },
            tileSize = 16,
            tileIconSize = 16,
            texture = "tileset",
            scale = 2,
            origin = "center",
            position = {
                x = Settings.video.resolution.x / 2,
                y = Settings.video.resolution.y / 2,
            },
        }
    }
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
            pop_state()
        end
    end
end

function Game:update(dt)
end

function Game:draw()
    return self.drawables
end