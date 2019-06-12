#pragma once


#include <Engine/ECS/RenderSystem.hpp>

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

class Scene
{
public:

        Scene(const std::string& stateType)
        : stateName(stateType + "_state")
        , render(entities)
        {
                const lua::Table classTable = script::luaContext.global[stateType];
                script::luaContext.global[this->stateName] = classTable["new"](classTable);

                const lua::Table thisObj = script::luaContext.global[this->stateName];
                const lua::Table entities = thisObj["entities"];
                
                for (int i = 1, nDrawables = entities.len(); i <= nDrawables; ++i)
                {
                        script::addEntity(this->entities, entities[i]);
                }
        }

        ~Scene()
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
                render.draw(target);
        }

private:

        std::string stateName;
        entt::registry entities;
        ecs::RenderSystem render;
};

}
