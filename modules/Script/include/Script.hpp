#pragma once


#include <Script/ECS.hpp>
#include <Script/Graphics.hpp>
#include <Script/Input.hpp>
#include <Script/Math.hpp>
#include <Script/Resources.hpp>
#include <Script/Scenes.hpp>
#include <Script/Table.hpp>


namespace script
{

inline static void init()
{
        lua.open_libraries(
                sol::lib::base,
                sol::lib::package,
                sol::lib::coroutine,
                sol::lib::string,
                sol::lib::os,
                sol::lib::math,
                sol::lib::table,
                sol::lib::debug,
                sol::lib::bit32,
                sol::lib::io,
                sol::lib::ffi,
                sol::lib::jit);

        loadECS();
        loadGraphics();
        loadInput();
        loadMath();
        loadResources();

        // Random
        lua["random"] = lua.create_table_with(
                "chance",   util::chance,
                "uniform",  util::uniform<double>,
                "iuniform", util::uniform<std::int32_t>,
                "normal",   util::normal<double>);

        // Settings
        lua.script_file("data/scripts/settings.lua");

        loadScenes();
        loadTable();

        // Run the game.
        lua.script_file("data/scripts/init.lua");
}

}