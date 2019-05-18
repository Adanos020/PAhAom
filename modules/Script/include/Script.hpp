#pragma once


#include <Script/ECS.hpp>
#include <Script/Graphics.hpp>
#include <Script/Math.hpp>
#include <Script/Observer.hpp>
#include <Script/Random.hpp>
#include <Script/Resources.hpp>
#include <Script/Window.hpp>


namespace script
{

void init()
{
        // Math.
        lua::Table math = luaContext.global["math"];
        math["clamp"]                  = clamp;
        math["lerp_number"]            = lerpNumber;
        math["normalize_number"]       = normalizeNumber;
        math["map_number"]             = mapNumber;
        math["is_vector"]              = isVector;
        math["vectors_equal"]          = vectorsEqual;
        math["vectors_lerp"]           = vectorLerp;
        math["vector_length_squared"]  = vectorLengthSquared;
        math["vector_length"]          = vectorLength;
        math["vector_normalize"]       = vectorNormalize;
        math["vector_set_length"]      = vectorSetLength;
        math["is_rectangle"]           = isRectangle;
        math["rectangles_intersect"]   = rectanglesIntersect;
        math["rectangle_contains"]     = rectangleContains;

        // Messages.
        luaContext.global["pop_state"]  = popState;
        luaContext.global["push_state"] = pushState;

        // Resources.
        luaContext.global["load_font"]    = load<sf::Font>;
        luaContext.global["load_texture"] = load<sf::Texture>;

        // Random.
        lua::Table random{luaContext};
        random["chance"]  = chance;
        random["uniform"] = uniform;
        random["normal"]  = normal;
        luaContext.global["random"] = random;

        luaState.runFile("data/scripts/init.lua");
}

}