#pragma once


#include <Script.hpp>

#include <Util/Constants.hpp>
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
                const lua::Table classTable = script::luaContext.global[stateType];
                script::luaContext.global[this->stateName] = classTable["new"](classTable);

                const lua::Table thisObj = script::luaContext.global[this->stateName];
                const lua::Table drawables = thisObj["drawables"];
                
                for (int i = 1, nDrawables = drawables.len(); i <= nDrawables; ++i)
                {
                        lua::Table drawable = drawables[i];
                        if (auto d = script::tableToDrawable(drawable))
                        {
                                this->drawables.push_back(std::move(d.value()));
                                drawable["index"] = i - 1; // Adding an index to the drawable recipe.
                        }
                        else
                        {
                                // Removing a wrongly defined drawable to avoid checking it every frame.
                                script::luaContext.global["table"]["remove"](drawables, i);
                                std::cerr << util::err::wrongDrawableDefinition(i) << std::endl;
                        }
                }
        }

        ~GameState()
        {
                script::luaContext.global[this->stateName] = lua::nil;
        }

        void handleInput(const sf::Event& event)
        {
                const lua::Table thisObj = script::luaContext.global[this->stateName];
                const lua::Table evt = script::eventToTable(event);
                thisObj["handle_input"](thisObj, evt);
        }

        void update()
        {
                const lua::Table thisObj = script::luaContext.global[this->stateName];
                thisObj["update"](thisObj, util::FRAME_TIME);
                // TODO - apply updates to actual objects.
        }

        void draw(sf::RenderTarget& target)
        {
                const lua::Table thisObj = script::luaContext.global[this->stateName];
                const lua::Table drawables = thisObj["draw"](thisObj);
                drawables.iterate([&](lua::Valref, lua::Valref drawable) {
                        const int index = drawable["index"];
                        target.draw(*this->drawables[index]);
                });
        }

private:

        std::string stateName;
        util::UniquePtrs<sf::Drawable> drawables;
};

}
