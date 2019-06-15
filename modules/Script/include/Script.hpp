#pragma once


#include <Script/Aux.hpp>
#include <Script/ECS.hpp>
#include <Script/Graphics.hpp>
#include <Script/Input.hpp>
#include <Script/Math.hpp>
#include <Script/Random.hpp>
#include <Script/Resources.hpp>
#include <Script/Scenes.hpp>


namespace script
{

inline static void init()
{
        // ECS
        luaContext.global["setPosition"] = setPosition;
        luaContext.global["setRotation"] = setRotation;
        luaContext.global["setScale"]    = setScale;

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

        luaState.runFile("data/scripts/init.lua");
}

}