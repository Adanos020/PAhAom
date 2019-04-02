-- Scripts to load.
scripts_path = "data/script/"
scripts = {
    "keyboard.lua",
    "settings.lua",
    "GameState/Menu.lua",
    "GameState/Game.lua",
}

for i,path in ipairs(scripts) do
    dofile(scripts_path .. path)
end