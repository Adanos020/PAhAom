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
        luaContext.global["is_vector"]            = isVector;
        luaContext.global["vectors_equal"]        = vectorsEqual;
        luaContext.global["is_rectangle"]         = isRectangle;
        luaContext.global["rectangles_intersect"] = rectanglesIntersect;
        luaContext.global["rectangle_contains"]   = rectangleContains;
        luaContext.global["math"]["clamp"]        = clamp;
        luaContext.global["math"]["lerp"]         = lerp;

        // Messages.
        luaContext.global["pop_state"]  = popState;
        luaContext.global["push_state"] = pushState;

        // Resources.
        luaContext.global["load_font"]    = load<sf::Font>;
        luaContext.global["load_texture"] = load<sf::Texture>;

        // Random.
        luaContext.global["chance"]  = chance;
        luaContext.global["uniform"] = uniform;
        luaContext.global["normal"]  = normal;

        luaState.runFile("data/scripts/init.lua");
}

}