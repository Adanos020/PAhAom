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
        : stateName(stateType + "_scene")
        {
                util::Subject::addObserver(this);

                // Construct the scene object.
                const lua::Table classTable = script::luaContext.global[stateType];
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

        ~Scene()
        {
                util::Subject::deleteObserver(this);
                script::luaContext.global[this->stateName] = lua::nil;
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
                else if (auto pos = std::get_if<util::Message::MoveBy>(&msg.msg))
                {
                        this->systems.transform.move(pos->entity, pos->displacement);
                }
                else if (auto rot = std::get_if<util::Message::RotateBy>(&msg.msg))
                {
                        this->systems.transform.rotate(rot->entity, rot->rotation);
                }
                else if (auto scl = std::get_if<util::Message::ScaleBy>(&msg.msg))
                {
                        this->systems.transform.scale(scl->entity, scl->scale);
                }
        }

private:

        std::string stateName;
        ecs::Systems systems;
};

}