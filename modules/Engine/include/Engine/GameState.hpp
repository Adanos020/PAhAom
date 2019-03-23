#pragma once


#include <selene.h>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <string>


#define S(x) this->state["x"]

namespace engine
{

/* 
 * 
 */
class GameState
{
public:

        GameState(const std::string& scriptPath)
        : state(true)
        {
                this->state.Load(scriptPath);
                S(state) = S(Menu:new)();
        }

        void handleInput(const sf::Event& event)
        {

        }

        void update()
        {

        }

        void draw(sf::RenderTarget& target, sf::RenderStates states)
        {

        }

private:

        sel::State state;
};

}

#undef S