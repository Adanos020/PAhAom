#pragma once


#include <Script/Graphics.hpp>
#include <Script/Observer.hpp>
#include <Script/Random.hpp>
#include <Script/Resources.hpp>
#include <Script/Window.hpp>


namespace script
{

void init()
{
        luaContext.global["push_state"]   = pushState;
        luaContext.global["pop_state"]    = popState;
        luaContext.global["load_font"]    = load<sf::Font>;
        luaContext.global["load_texture"] = load<sf::Texture>;
        luaContext.global["chance"]       = chance;
        luaContext.global["uniform"]      = uniform;
        luaContext.global["normal"]       = normal;
        luaState.runFile("data/scripts/init.lua");
}

}