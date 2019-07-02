#pragma once


#include <Script/ECS.hpp>
#include <Script/Graphics.hpp>
#include <Script/Input.hpp>
#include <Script/Math.hpp>
#include <Script/Random.hpp>
#include <Script/Resources.hpp>
#include <Script/Scenes.hpp>
#include <Script/Table.hpp>


namespace script
{

inline static void init()
{
        // ECS
        luaContext.global["entity"] = lua::Table::records(luaContext,
                "add",          addEntity,
                "setPosition",  setPosition,
                "setRotation",  setRotation,
                "setScale",     setScale,
                "moveBy",       moveBy,
                "rotateBy",     rotateBy,
                "scaleBy",      scaleBy,
                "setVelocity",  setVelocity,
                "accelerateBy", accelerateBy,
                "setMass",      setMass);


        // Graphics
        luaContext.global["rgba"] = rgba;
        luaContext.global["rgb"]  = rgb;


        // Input
        luaState.runString(R"(
                keyNames = {
                        [-1] = "unknown", [0] = "a", "b", "c",
                        "d", "e", "f", "g",
                        "h", "i", "j", "k",
                        "l", "m", "n", "o",
                        "p", "q", "r", "s",
                        "t", "u", "v", "w",
                        "x", "y", "z", "num0",
                        "num1", "num2", "num3", "num4",
                        "num5", "num6", "num7", "num8",
                        "num9", "escape", "lControl", "lShift",
                        "lAlt", "lSystem", "rControl", "rShift",
                        "rAlt", "rSystem", "menu", "lBracket",
                        "rBracket", "semicolon", "comma", "period",
                        "quote", "slash", "backslash", "tilde",
                        "equal", "hyphen", "space", "enter",
                        "backspace", "tab", "pageUp", "pageDown",
                        "end", "home", "insert", "delete",
                        "add", "subtract", "multiply", "divide",
                        "left", "right", "up", "down",
                        "numpad0", "numpad1", "numpad2", "numpad3",
                        "numpad4", "numpad5", "numpad6", "numpad7",
                        "numpad8", "numpad9", "f1", "f2",
                        "f3", "f4", "f5", "f6",
                        "f7", "f8", "f9", "f10",
                        "f11", "f12", "f13", "f14",
                        "f15", "pause", "keyCount"
                }
                keyboard = {}
                for i = -1, #keyNames do
                        keyboard[keyNames[i]] = i
                end
        )");


        // Math
        lua::Table math = luaContext.global["math"];
        math["clamp"]     = clamp;
        math["lerp"]      = numberLerp;
        math["normalize"] = numberNormalize;
        math["map"]       = numberMap;

        luaContext.global["vector"]   = vector;
        luaContext.global["isVector"] = isVector;
        
        // Would've used lua::Table::records for this table, however
        // it seems that it's too many arguments for this case and
        // the memory for this table is allocated inappropriately,
        // resulting in segmentation faults on exit. Just fucking wow.
        auto vec = lua::Table{luaContext};
        vec["equals"]        = vectorEquals;
        vec["add"]           = vectorAdd;
        vec["subtract"]      = vectorSubtract;
        vec["multiply"]      = vectorMultiply;
        vec["divide"]        = vectorDivide;
        vec["inverse"]       = vectorInverse;
        vec["lengthSquared"] = vectorLengthSquared;
        vec["length"]        = vectorLength;
        vec["setLength"]     = vectorSetLength;
        vec["limit"]         = vectorLimit;
        vec["normalize"]     = vectorNormalize;
        vec["clampToArea"]   = vectorClampToArea;
        vec["clampToLength"] = vectorClampToLength;
        vec["fromPolar"]     = vectorFromPolar;
        vec["dot"]           = vectorDot;
        vec["angleBetween"]  = vectorAngleBetween;
        vec["lerp"]          = vectorLerp;
        luaContext.global["vec"] = vec;
        
        luaContext.global["rectangle"] = rectangle;
        luaContext.global["isRectangle"] = isRectangle;
        luaContext.global["rect"] = lua::Table::records(luaContext,
                "contains",   rectangleContains,
                "intersects", rectangleIntersects);


        // Resources
        addResourceHandlerTable<sf::Font>("fonts");
        addResourceHandlerTable<sf::Texture>("textures");
        luaState.runFile("data/scripts/resources.lua");

        lua::Table resources = luaContext.global["resources"];
        static_cast<lua::Table>(resources["fonts"]).iterate([](lua::Valref, lua::Valref res)
        {
                engine::Resources<sf::Font>::load(res[1], "data/fonts/" & res[2]);
        });

        static_cast<lua::Table>(resources["textures"]).iterate([](lua::Valref, lua::Valref res)
        {
                engine::Resources<sf::Texture>::load(res[1], "data/textures/" & res[2]);
        });


        // Random
        luaContext.global["random"] = lua::Table::records(luaContext,
                "chance",  chance,
                "uniform", uniform,
                "normal",  normal);

        // Scenes
        luaContext.global["game"] = lua::Table::records(luaContext,
                "switchTo",  switchTo,
                "saveScene", saveScene,
                "loadScene", loadScene,
                "quit",      quit);


        // Settings
        luaState.runFile("data/scripts/settings.lua");


        // Table
        luaContext.global["allOf"]  = allOf;
        luaContext.global["anyOf"]  = anyOf;
        luaContext.global["noneOf"] = noneOf;


        // Run the game.
        luaState.runFile("data/scripts/init.lua");
}

}