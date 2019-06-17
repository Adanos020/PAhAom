#pragma once


#include <Script/Aux.hpp>
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
        luaContext.global["addEntity"]   = addEntity;
        luaContext.global["setPosition"] = setPosition;
        luaContext.global["setRotation"] = setRotation;
        luaContext.global["setScale"]    = setScale;


        // Input
        luaState.runString(
                "KeyNames = {\n"
                "        [-1] = 'Unknown', [0] = 'A', 'B', 'C',\n"
                "        'D', 'E', 'F', 'G',\n"
                "        'H', 'I', 'J', 'K',\n"
                "        'L', 'M', 'N', 'O',\n"
                "        'P', 'Q', 'R', 'S',\n"
                "        'T', 'U', 'V', 'W',\n"
                "        'X', 'Y', 'Z', 'Num0',\n"
                "        'Num1', 'Num2', 'Num3', 'Num4',\n"
                "        'Num5', 'Num6', 'Num7', 'Num8',\n"
                "        'Num9', 'Escape', 'LControl', 'LShift',\n"
                "        'LAlt', 'LSystem', 'RControl', 'RShift',\n"
                "        'RAlt', 'RSystem', 'Menu', 'LBracket',\n"
                "        'RBracket', 'Semicolon', 'Comma', 'Period',\n"
                "        'Quote', 'Slash', 'Backslash', 'Tilde',\n"
                "        'Equal', 'Hyphen', 'Space', 'Enter',\n"
                "        'Backspace', 'Tab', 'PageUp', 'PageDown',\n"
                "        'End', 'Home', 'Insert', 'Delete',\n"
                "        'Add', 'Subtract', 'Multiply', 'Divide',\n"
                "        'Left', 'Right', 'Up', 'Down',\n"
                "        'Numpad0', 'Numpad1', 'Numpad2', 'Numpad3',\n"
                "        'Numpad4', 'Numpad5', 'Numpad6', 'Numpad7',\n"
                "        'Numpad8', 'Numpad9', 'F1', 'F2',\n"
                "        'F3', 'F4', 'F5', 'F6',\n"
                "        'F7', 'F8', 'F9', 'F10',\n"
                "        'F11', 'F12', 'F13', 'F14',\n"
                "        'F15', 'Pause', 'KeyCount'\n"
                "}\n"
                "Keyboard = {}\n"
                "for i = -1, #KeyNames do\n"
                "        Keyboard[KeyNames[i]] = i\n"
                "end"
        );


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
        luaContext.global["loadFont"]    = load<sf::Font>;
        luaContext.global["loadTexture"] = load<sf::Texture>;


        // Random
        lua::Table random{luaContext};
        random["chance"]  = chance;
        random["uniform"] = uniform;
        random["normal"]  = normal;
        luaContext.global["random"] = random;


        // Scenes
        luaContext.global["popScene"]  = popScene;
        luaContext.global["pushScene"] = pushScene;


        // Settings and resources
        luaState.runFile("data/scripts/settings.lua");
        luaState.runFile("data/scripts/resources.lua");

        lua::Table resources = luaContext.global["Resources"];
        static_cast<lua::Table>(resources["fonts"]).iterate([](lua::Valref, lua::Valref res)
        {
                engine::Resources::load<sf::Font>(res[1], "data/fonts/" & res[2]);
        });

        static_cast<lua::Table>(resources["textures"]).iterate([](lua::Valref, lua::Valref res)
        {
                engine::Resources::load<sf::Texture>(res[1], "data/textures/" & res[2]);
        });


        // Table
        lua::Table table = luaContext.global["table"];
        table["all"]  = tableAll;
        table["any"]  = tableAny;
        table["none"] = tableNone;


        // Run the game.
        luaState.runFile("data/scripts/init.lua");
}

}