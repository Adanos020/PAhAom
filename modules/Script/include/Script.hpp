#pragma once


#include <Script/Graphics.hpp>
#include <Script/Math.hpp>
#include <Script/Observer.hpp>
#include <Script/Random.hpp>
#include <Script/Resources.hpp>
#include <Script/Window.hpp>


namespace script
{

inline static void init()
{
        // Math.
        lua::Table math = luaContext.global["math"];
        math["clamp"]     = clamp;
        math["lerp"]      = numberLerp;
        math["normalize"] = numberNormalize;
        math["map"]       = numberMap;
        
        math["is_vector"]              = isVector;
        math["vectors_equal"]          = vectorsEqual;
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

template<typename Return>
inline static Return hasOpt(const lua::Table& v, const std::string& name, const Return rFalse)
{
        if (v[name])
        {
                if constexpr (std::is_fundamental_v<Return>)
                {
                        return v[name].to<Return>();
                }
                else
                {
                        return Return(lua::Table(v[name]));
                }
        }
        return rFalse;
}

}