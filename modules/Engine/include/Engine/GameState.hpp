#pragma once


#include <Util/Constants.hpp>
#include <Util/Script.hpp>
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
                const lua::Table classTable = util::luaContext.global[stateType];
                util::luaContext.global[this->stateName] = classTable["new"](classTable);

                const lua::Table thisObj = util::luaContext.global[this->stateName];
                const lua::Table drawables = thisObj["drawables"];
                
                for (int i = 1, nDrawables = drawables.len(); i <= nDrawables; ++i)
                {
                        lua::Table drawable = drawables[i];
                        this->drawableObjects.push_back(util::script::tableToDrawable(drawable));
                        if (not this->drawableObjects.back().get())
                        {
                                std::cerr << util::err::wrongDrawableDefinition(i) << std::endl;
                                this->drawableObjects.pop_back();
                                break;
                        }

                        // Changing the drawable's recipe to its index.
                        drawable["index"] = i - 1;
                }
        }

        ~GameState()
        {
                util::luaContext.global[this->stateName] = lua::nil;
        }

        auto handleInput(const sf::Event& event) -> void
        {
                const lua::Table evt = util::script::eventToTable(event);
                const lua::Table thisObj = util::luaContext.global[this->stateName];
                thisObj["handle_input"](thisObj, evt);
        }

        auto update() -> void
        {
                const lua::Table thisObj = util::luaContext.global[this->stateName];
                thisObj["update"](thisObj, util::FRAME_TIME);
        }

        auto draw(sf::RenderTarget& target) -> void
        {
                const lua::Table thisObj = util::luaContext.global[this->stateName];
                const lua::Table drawables = thisObj["draw"](thisObj);

                drawables.iterate([&](lua::Valref, lua::Valref drawable) {
                        target.draw(*drawableObjects[int(drawable["index"])]);
                });
        }

private:

        std::string stateName;
        util::UniquePtrs<sf::Drawable> drawableObjects;
};

}
