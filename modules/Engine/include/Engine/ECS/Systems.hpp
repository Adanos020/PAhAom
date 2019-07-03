#pragma once


#include <Engine/ECS/InputSystem.hpp>
#include <Engine/ECS/PhysicsSystem.hpp>
#include <Engine/ECS/RenderSystem.hpp>
#include <Engine/ECS/TransformSystem.hpp>

#include <Util/Observer.hpp>

#include <entt/entity/registry.hpp>


namespace engine::ecs
{

class Systems : public util::Observer
{
public:

        Systems()
        : physics(entities)
        , render(entities)
        , transform(entities)
        {
                util::Subject::addObserver(this);
        }

        ~Systems()
        {
                util::Subject::deleteObserver(this);
        }

        void addEntity(sol::table entityTable)
        {
                const entt::entity entity = this->entities.create();
                entityTable["id"] = entity;

                this->input.assignInput(entityTable);
                this->physics.assignPhysics(entity, entityTable);
                this->transform.assignTransform(entity, entityTable);
                this->render.assignGraphics(entity, entityTable);
        }

        void reset()
        {
                this->input.clearKeys();
                this->entities.reset();
        }

public:

        InputSystem input;
        PhysicsSystem physics;
        RenderSystem render;
        TransformSystem transform;

private:

        virtual void receive(const util::Message& message) override
        {
                std::visit(util::MsgHandlers {
                        [this](const util::Message::AddEntity& msg)
                        {
                                this->addEntity(msg.data);
                        },
                        util::discardTheRest
                }, message.msg);
        }

private:

        entt::registry entities;
};

}