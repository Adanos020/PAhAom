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

        virtual void receive(const util::Message& message) override
        {
                std::visit(util::MsgHandlers {
                        [this](const util::Message::AddEntity& msg)
                        {
                                lua::Table entity = msg.data;
                                this->systems.addEntity(entity);
                        },
                        [this](const util::Message::SetEntityPosition& msg)
                        {
                                this->systems.transform.setPosition(msg.entity, msg.position);
                        },
                        [this](const util::Message::SetEntityRotation& msg)
                        {
                                this->systems.transform.setRotation(msg.entity, msg.rotation);
                        },
                        [this](const util::Message::SetEntityScale& msg)
                        {
                                this->systems.transform.setScale(msg.entity, msg.scale);
                        },
                        [this](const util::Message::MoveEntityBy& msg)
                        {
                                this->systems.transform.move(msg.entity, msg.displacement);
                        },
                        [this](const util::Message::RotateEntityBy& msg)
                        {
                                this->systems.transform.rotate(msg.entity, msg.rotation);
                        },
                        [this](const util::Message::ScaleEntityBy& msg)
                        {
                                this->systems.transform.scale(msg.entity, msg.scale);
                        },
                        [](const auto& discard [[maybe_unused]]) {},
                }, message.msg);
        }

private:

        std::string stateName;
        ecs::Systems systems;
};

}