#pragma once


#include <Script/Graphics.hpp>
#include <Script/Observer.hpp>
#include <Script/Math.hpp>
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
        math["is_vector2"]             = isVector<2>;
        math["is_vector3"]             = isVector<3>;
        math["vector2s_equal"]         = vectorsEqual<2>;
        math["vector3s_equal"]         = vectorsEqual<3>;
        math["vector2s_lerp"]          = vectorLerp<2>;
        math["vector3s_lerp"]          = vectorLerp<3>;
        math["vector2_length_squared"] = vectorLengthSquared<2>;
        math["vector3_length_squared"] = vectorLengthSquared<3>;
        math["vector2_length"]         = vectorLength<2>;
        math["vector3_length"]         = vectorLength<3>;
        math["vector2_normalize"]      = vectorNormalize<2>;
        math["vector3_normalize"]      = vectorNormalize<3>;
        math["vector2_set_length"]     = vectorSetLength<2>;
        math["vector3_set_length"]     = vectorSetLength<3>;
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