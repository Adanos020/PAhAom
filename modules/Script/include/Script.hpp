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
                "add", addEntity,
                "setPosition", setPosition,
                "setRotation", setRotation,
                "setScale", setScale,
                "moveBy", moveBy,
                "rotateBy", rotateBy,
                "scaleBy", scaleBy);


        // Graphics
        luaContext.global["rgba"] = rgba;
        luaContext.global["rgb"]  = rgb;


        // Input
        luaState.runString(R"(
                KeyNames = {
                        [-1] = "Unknown", [0] = "A", "B", "C",
                        "D", "E", "F", "G",
                        "H", "I", "J", "K",
                        "L", "M", "N", "O",
                        "P", "Q", "R", "S",
                        "T", "U", "V", "W",
                        "X", "Y", "Z", "Num0",
                        "Num1", "Num2", "Num3", "Num4",
                        "Num5", "Num6", "Num7", "Num8",
                        "Num9", "Escape", "LControl", "LShift",
                        "LAlt", "LSystem", "RControl", "RShift",
                        "RAlt", "RSystem", "Menu", "LBracket",
                        "RBracket", "Semicolon", "Comma", "Period",
                        "Quote", "Slash", "Backslash", "Tilde",
                        "Equal", "Hyphen", "Space", "Enter",
                        "Backspace", "Tab", "PageUp", "PageDown",
                        "End", "Home", "Insert", "Delete",
                        "Add", "Subtract", "Multiply", "Divide",
                        "Left", "Right", "Up", "Down",
                        "Numpad0", "Numpad1", "Numpad2", "Numpad3",
                        "Numpad4", "Numpad5", "Numpad6", "Numpad7",
                        "Numpad8", "Numpad9", "F1", "F2",
                        "F3", "F4", "F5", "F6",
                        "F7", "F8", "F9", "F10",
                        "F11", "F12", "F13", "F14",
                        "F15", "Pause", "KeyCount"
                }
                Keyboard = {}
                for i = -1, #KeyNames do
                        Keyboard[KeyNames[i]] = i
                end
        )");


        // Math
        lua::Table math = luaContext.global["math"];
        math["clamp"]     = clamp;
        math["lerp"]      = numberLerp;
        math["normalize"] = numberNormalize;
        math["map"]       = numberMap;
        
        math["vector"]              = vector;
        math["isVector"]            = isVector;
        math["vectorEquals"]        = vectorEquals;
        math["vectorAdd"]           = vectorAdd;
        math["vectorSubtract"]      = vectorSubtract;
        math["vectorMultiply"]      = vectorMultiply;
        math["vectorDivide"]        = vectorDivide;
        math["vectorInverse"]       = vectorInverse;
        math["vectorLengthSquared"] = vectorLengthSquared;
        math["vectorLength"]        = vectorLength;
        math["vectorSetLength"]     = vectorSetLength;
        math["vectorLimit"]         = vectorLimit;
        math["vectorNormalize"]     = vectorNormalize;
        math["vectorClampToArea"]   = vectorClampToArea;
        math["vectorClampToLength"] = vectorClampToLength;
        math["vectorFromPolar"]     = vectorFromPolar;
        math["vectorDot"]           = vectorDot;
        math["vectorAngleBetween"]  = vectorAngleBetween;
        math["vectorLerp"]          = vectorLerp;
        
        math["isRectangle"]         = isRectangle;
        math["rectangleContains"]   = rectangleContains;
        math["rectangleIntersects"] = rectangleIntersects;


        // Resources
        luaContext.global["fonts"] = lua::Table::records(luaContext,
                "load", load<sf::Font>,
                "unload", unload<sf::Font>,
                "unloadAll", unloadAll<sf::Font>);
        luaContext.global["textures"] = lua::Table::records(luaContext,
                "load", load<sf::Texture>,
                "unload", unload<sf::Texture>,
                "unloadAll", unloadAll<sf::Texture>);
        luaState.runFile("data/scripts/resources.lua");

        lua::Table resources = luaContext.global["Resources"];
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
                "chance", chance,
                "uniform", uniform,
                "normal", normal);

        // Scenes
        luaContext.global["popScene"]  = popScene;  // deprecated
        luaContext.global["pushScene"] = pushScene; // deprecated
        luaContext.global["scene"] = lua::Table::records(luaContext,
                "switchTo", switchScene,
                "saveAndSwitchTo", saveAndSwitchScene,
                "load", loadScene,
                "saveAndLoad", saveAndLoadScene,
                "quit", quit,
                "saveAndQuit", saveAndQuit);


        // Settings
        luaState.runFile("data/scripts/settings.lua");


        // Table
        lua::Table table = luaContext.global["table"];
        table["all"]  = tableAll;
        table["any"]  = tableAny;
        table["none"] = tableNone;


        // Run the game.
        luaState.runFile("data/scripts/init.lua");
}

}