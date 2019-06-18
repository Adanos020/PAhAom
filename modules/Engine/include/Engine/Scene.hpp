#pragma once


#include <Engine/ECS/Systems.hpp>

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
        {
                util::Subject::addObserver(this);

                // Construct the scene object.
                const lua::Table classTable = script::luaContext.global[stateType];
                script::luaContext.global[this->stateName] = classTable["new"](classTable);

                const lua::Table thisObj = script::luaContext.global[this->stateName];

                // Add empty event handlers for unhandled events.
                for (std::size_t i = 0; i < sf::Event::Count; ++i)
                {
                        if (!thisObj[EVENT_HANDLERS[i]].is<lua::LFunction>())
                        {
                                const auto emptyHandler = [](lua::Context& c) { return c.ret(); };
                                thisObj[EVENT_HANDLERS[i]] = emptyHandler;
                        }
                }

                // Propagate the ECS with predefined entities.
                const lua::Table entities = thisObj["entities"];
                entities.iterate([this](lua::Valref, lua::Valref el)
                {
                        lua::Table entity = el;
                        this->systems.addEntity(entity);
                });
        }

        ~Scene()
        {
                util::Subject::deleteObserver(this);
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
                thisObj["update"](thisObj, util::FRAME_TIME.asSeconds());
        }

        void draw(sf::RenderTarget& target)
        {
                this->systems.render.drawTo(target);
        }

public:

        virtual void receive(const util::Message& msg) override
        {
                if (auto pos = std::get_if<util::Message::AddEntity>(&msg.msg))
                {
                        lua::Table entity = pos->data;
                        this->systems.addEntity(entity);
                }
                else if (auto pos = std::get_if<util::Message::SetPosition>(&msg.msg))
                {
                        this->systems.transform.setPosition(pos->entity, pos->position);
                }
                else if (auto rot = std::get_if<util::Message::SetRotation>(&msg.msg))
                {
                        this->systems.transform.setRotation(rot->entity, rot->rotation);
                }
                else if (auto scl = std::get_if<util::Message::SetScale>(&msg.msg))
                {
                        this->systems.transform.setScale(scl->entity, scl->scale);
                }
        }

private:

        std::string stateName;
        ecs::Systems systems;
        inline static constexpr util::CStr EVENT_HANDLERS[sf::Event::Count] = {
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