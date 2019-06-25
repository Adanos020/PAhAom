#pragma once


#include <Engine/ECS/Systems.hpp>

#include <Script.hpp>

#include <Util/Constants.hpp>
#include <Util/Math.hpp>
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

        Scene()
        {
                util::Subject::addObserver(this);
        }

        Scene(const std::string& sceneName)
        : Scene()
        {
                this->switchTo(sceneName);
        }

        ~Scene()
        {
                util::Subject::deleteObserver(this);
                this->reset();
        }

        void reset()
        {
                this->systems.reset();
                script::luaContext.global[this->stateName] = lua::nil;
        }

        void switchTo(const std::string& sceneName)
        {
                this->reset();

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

        virtual void receive(const util::Message& msg) override
        {
                const auto id = static_cast<util::MessageID>(msg.msg.index());

                // if (not util::isWithin(id, util::MessageID::AddEntity, util::MessageID::ScaleEntityBy))
                // {
                //         return;
                // }

                switch (id)
                {
                        case util::MessageID::AddEntity:
                        {
                                lua::Table entity = std::get<util::Message::AddEntity>(msg.msg).data;
                                this->systems.addEntity(entity);
                                break;
                        }
                        case util::MessageID::SetEntityPosition:
                        {
                                auto pos = std::get<util::Message::SetEntityPosition>(msg.msg);
                                this->systems.transform.setPosition(pos.entity, pos.position);
                                break;
                        }
                        case util::MessageID::SetEntityRotation:
                        {
                                auto rot = std::get<util::Message::SetEntityRotation>(msg.msg);
                                this->systems.transform.setRotation(rot.entity, rot.rotation);
                                break;
                        }
                        case util::MessageID::SetEntityScale:
                        {
                                auto scl = std::get<util::Message::SetEntityScale>(msg.msg);
                                this->systems.transform.setScale(scl.entity, scl.scale);
                                break;
                        }
                        case util::MessageID::MoveEntityBy:
                        {
                                auto pos = std::get<util::Message::MoveEntityBy>(msg.msg);
                                this->systems.transform.move(pos.entity, pos.displacement);
                                break;
                        }
                        case util::MessageID::RotateEntityBy:
                        {
                                auto rot = std::get<util::Message::RotateEntityBy>(msg.msg);
                                this->systems.transform.rotate(rot.entity, rot.rotation);
                                break;
                        }
                        case util::MessageID::ScaleEntityBy:
                        {
                                auto scl = std::get<util::Message::ScaleEntityBy>(msg.msg);
                                this->systems.transform.scale(scl.entity, scl.scale);
                                break;
                        }
                        default: break;
                }
        }

private:

        std::string stateName;
        ecs::Systems systems;
};

}