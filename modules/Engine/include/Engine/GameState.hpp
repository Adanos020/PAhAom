#pragma once


#include <Util/Constants.hpp>
#include <Util/Lua.hpp>
#include <Util/Types.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>
#include <memory>
#include <string>


namespace engine
{

/**
 * 
 */
class GameState
{
public:

        GameState(const std::string& stateType)
        : stateName(stateType + "_state")
        {
                using util::Lua;

                Lua::setVariable(this->stateName, stateType + ":new()");

                sel::Selector drawables = Lua::getVariable(this->stateName)["drawables"];
                util::LuaVariable temp{ "temp", std::string("#") + this->stateName + ".drawables" };
                
                for (int i = 1, nDrawables = temp.get(); i <= nDrawables; ++i)
                {
                        this->drawableObjects.push_back(Lua::tableToDrawable(drawables[i]));
                        if (not this->drawableObjects.back().get())
                        {
                                std::cerr << "Error: the following drawable definition is incorrect:" << std::endl;
                                this->drawableObjects.pop_back();
                                break;
                        }

                        // Changing the drawable's recipe to its index.
                        drawables[i] = i - 1;
                }
        }

        void handleInput(const sf::Event& event)
        {

        }

        void update()
        {
                // util::Lua::getVariable(this->stateName)["update"](lua_Number(util::FRAME_TIME));
                util::Lua::runCode(this->stateName + ":update(" + std::to_string(util::FRAME_TIME) + ")");
        }

        void draw(sf::RenderTarget& target)
        {
                using util::Lua;

                sel::Selector drawables = Lua::getVariable(this->stateName)["drawables"];
                util::LuaVariable temp{ "temp", std::string("#") + this->stateName + ":draw()" };

                for (int i = 1, nDrawables = temp.get(); i <= nDrawables; ++i)
                {
                        if (sel::Selector drawable = drawables[i]; Lua::hasType(drawable, "number"))
                        {
                                std::cout << "draw" << std::endl;
                                target.draw(*drawableObjects[int(drawable)]);
                        }
                }
        }

private:

        std::string stateName;
        util::UniquePtrs<sf::Drawable> drawableObjects;
};

}
