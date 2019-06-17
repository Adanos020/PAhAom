#pragma once


#include <Engine/ECS/RenderSystem.hpp>
#include <Engine/ECS/Script.hpp>
#include <Engine/ECS/TransformSystem.hpp>

#include <Script.hpp>

#include <Util/Constants.hpp>
#include <Util/Observer.hpp>
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

class Scene : public util::Observer
{
public:

        Scene(const std::string& stateType)
        : stateName(stateType + "_state")
        , render(entities)
        , transform(entities)
        {
                util::Subject::addObserver(this);

                // Construct the scene object.
                const lua::Table classTable = script::luaContext.global[stateType];
                script::luaContext.global[this->stateName] = classTable["new"](classTable);

                const lua::Table thisObj = script::luaContext.global[this->stateName];

                // Add empty event handlers for unhandled events.
                for (size_t i = 0; i < sf::Event::Count; ++i)
                {
                        if (!thisObj[EVENT_HANDLERS[i]].is<lua::LFunction>())
                        {
                                const auto emptyHandler = [](lua::Context& c) { return c.ret(); };
                                thisObj[EVENT_HANDLERS[i]] = emptyHandler;
                        }
                }

                // Propagate the ECS with predefined entities.
                const lua::Table entities = thisObj["entities"];
                for (int i = 1, nDrawables = entities.len(); i <= nDrawables; ++i)
                {
                        lua::Table entity = entities[i];
                        ecs::addEntity(this->entities, entity);
                }
        }

        ~Scene()
        {
                script::luaContext.global[this->stateName] = lua::nil;
        }

        void handleInput(const sf::Event& event)
        {
                const lua::Table thisObj = script::luaContext.global[this->stateName];
                const lua::Valset args = script::eventToHandlerArgs(thisObj, event);
                thisObj[EVENT_HANDLERS[event.type]](args);
        }

        void update()
        {
                const lua::Table thisObj = script::luaContext.global[this->stateName];
                thisObj["update"](thisObj, util::FRAME_TIME);
        }

        void draw(sf::RenderTarget& target)
        {
                render.draw(target);
        }

public:

        virtual void receive(const util::Message& msg) override
        {
                if (auto pos = std::get_if<util::Message::AddEntity>(&msg.msg))
                {
                        lua::Table entity = pos->data;
                        ecs::addEntity(this->entities, entity);
                }
                else if (auto pos = std::get_if<util::Message::SetPosition>(&msg.msg))
                {
                        this->transform.setPosition(pos->entity, pos->position);
                }
                else if (auto rot = std::get_if<util::Message::SetRotation>(&msg.msg))
                {
                        this->transform.setRotation(rot->entity, rot->rotation);
                }
                else if (auto scl = std::get_if<util::Message::SetScale>(&msg.msg))
                {
                        this->transform.setScale(scl->entity, scl->scale);
                }
        }

private:

        std::string stateName;
        entt::registry entities;
        
        ecs::RenderSystem render;
        ecs::TransformSystem transform;

        inline static const std::string EVENT_HANDLERS[] = {
                "onClosed",
                "onResized",
                "onLostFocus",
                "onGainedFocus",
                "onTextEntered",
                "onKeyPressed",
                "onKeyReleased",
                "onMouseWheelMoved",
                "onMouseWheelScrolled",
                "onMousePressed",
                "onMouseReleased",
                "onMouseMoved",
                "onMouseEntered",
                "onMouseLeft",
                "onJoystickPressed",
                "onJoystickReleased",
                "onJoystickMoved",
                "onJoystickConnected",
                "onJoystickDisconnected",
                "onTouchBegan",
                "onTouchMoved",
                "onTouchEnded",
                "onSensorChanged",
        };
};

}