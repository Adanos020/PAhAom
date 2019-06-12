#pragma once


#include <Script/Aux.hpp>
#include <Script/ECS.hpp>
#include <Script/Graphics.hpp>
#include <Script/Math.hpp>
#include <Script/Random.hpp>
#include <Script/Resources.hpp>
#include <Script/Scenes.hpp>
#include <Script/Window.hpp>


namespace script
{

inline static void init()
{
        // ECS
        luaContext.global["set_position"] = setPosition;
        luaContext.global["set_rotation"] = setRotation;
        luaContext.global["set_scale"]    = setScale;

        // Math
        lua::Table math = luaContext.global["math"];
        math["clamp"]     = clamp;
        math["lerp"]      = numberLerp;
        math["normalize"] = numberNormalize;
        math["map"]       = numberMap;
        
        math["is_vector"]              = isVector;
        math["vector_equal"]           = vectorsEqual;
        math["vector_add"]             = vectorsAdd;
        math["vector_length_squared"]  = vectorLengthSquared;
        math["vector_set_length"]      = vectorSetLength;
        math["vector_length"]          = vectorLength;
        math["vector_limit"]           = vectorLimit;
        math["vector_normalize"]       = vectorNormalize;
        math["vector_clamp_to_area"]   = vectorClampToArea;
        math["vector_clamp_to_length"] = vectorClampToLength;
        math["vector_from_polar"]      = vectorFromPolar;
        math["vector_dot"]             = vectorDot;
        math["vector_angle_between"]   = vectorAngleBetween;
        math["vector_lerp"]            = vectorLerp;
        
        math["is_rectangle"]         = isRectangle;
        math["rectangle_contains"]   = rectangleContains;
        math["rectangle_intersects"] = rectangleIntersects;

        // Messages
        luaContext.global["pop_state"]  = popScene;
        luaContext.global["push_state"] = pushScene;

        // Resources
        luaContext.global["load_font"]    = load<sf::Font>;
        luaContext.global["load_texture"] = load<sf::Texture>;

        // Random
        lua::Table random{luaContext};
        random["chance"]  = chance;
        random["uniform"] = uniform;
        random["normal"]  = normal;
        luaContext.global["random"] = random;

        luaState.runFile("data/scripts/init.lua");
}

}