#pragma once

#include <Script/Lua.hpp>

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>

namespace script
{

void callInputHandler(sol::table obj, sol::table handlers, sf::Event event);

void loadInput(sf::Window& window);

}
