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
                script::lua[this->stateName] = sol::nil;
        }

        void switchTo(const std::string& sceneName)
        {
                this->destroy();

                // Construct the scene object.
                sol::table classTable = script::lua[sceneName];
                script::lua[this->stateName] = classTable["new"](classTable);

                sol::table thisObj = script::lua[this->stateName];

                // Add predefined entities.
                sol::table entities = thisObj["entities"];
                entities.for_each([this](sol::object, sol::object el)
                {
                        if (el.get_type() == sol::type::table)
                        {
                                sol::table entity = el;
                                this->systems.addEntity(entity);
                        }
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
                sol::table thisObj = script::lua[this->stateName];
                
                this->systems.input.handleInput(event);
                script::callInputHandler(thisObj, thisObj, event);
        }

        void update()
        {
                sol::table thisObj = script::lua[this->stateName];
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