#pragma once


#include <Engine/ECS/Systems.hpp>

#include <Script/Lua.hpp>
#include <Script/Input.hpp>

#include <Util/Constants.hpp>
#include <Util/Math.hpp>
#include <Util/Types.hpp>

#include <SFML/Graphics/Drawable.hpp>
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

        Scene()
        {
        }

        Scene(const std::string& sceneName)
        : Scene()
        {
                this->switchTo(sceneName);
        }

        ~Scene()
        {
                this->destroy();
        }

        void destroy()
        {
                this->systems.reset();
                script::luaContext.global[this->stateName] = lua::nil;
        }

        void switchTo(const std::string& sceneName)
        {
                this->destroy();

                // Construct the scene object.
                const lua::Table classTable = script::luaContext.global[sceneName];
                script::luaContext.global[this->stateName] = classTable["new"](classTable);

                lua::Table thisObj = script::luaContext.global[this->stateName];
                script::assignEmptyInputHandlers(thisObj);

                // Add predefined entities.
                const lua::Table entities = thisObj["entities"];
                entities.iterate([this](lua::Valref, lua::Valref el)
                {
                        this->systems.addEntity(el);
                });
        }

        void load(const util::SceneID)
        {
                this->destroy();
        }

        void save(util::SceneID id)
        {
                if (!id)
                {
                        id = ++currentId;
                }
        }

        void handleInput(const sf::Event& event)
        {
                const lua::Table thisObj = script::luaContext.global[this->stateName];
                const std::string which = script::EVENT_HANDLERS[event.type];
                
                auto args = lua::Valset{thisObj};
                script::addInputHandlerArgs(args, event);
                
                this->systems.input.handleInput(event, args);
                args[0] = thisObj;
                thisObj[which](args);
        }

        void update()
        {
                const lua::Table thisObj = script::luaContext.global[this->stateName];
                thisObj["update"](thisObj, util::FRAME_TIME.asSeconds());
                this->systems.physics.update();
        }

        void drawTo(sf::RenderTarget& target)
        {
                this->systems.render.drawTo(target);
        }

public:

        static util::SceneID nextId()
        {
                return currentId + 1;
        }

private:

        inline static util::SceneID currentId = 0;

        std::string stateName;
        ecs::Systems systems;
};

}