dofile "data/scripts/scripts.lua"

for _, path in ipairs(scripts) do
    dofile("data/scripts/" .. path)
end

for _, font in ipairs(Resources.fonts) do
    local id = font[1]
    local path = "data/fonts/" .. font[2]
    if not loadFont(id, path) then
        print(string.format("Font '%s' could not be loaded from '%s'.", id, path))
    end
end

for _, texture in ipairs(Resources.textures) do
    local id = texture[1]
    local path = "data/textures/" .. texture[2]
    if not loadTexture(id, path) then
        print(string.format("Texture '%s' could not be loaded from '%s'.", id, path))
    end
end

-- Initial state.
pushScene "Menu"