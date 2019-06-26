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

        void addEntity(lua::Valref entityTable)
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
                                lua::Table entity = msg.data;
                                this->addEntity(entity);
                        },
                        [this](const util::Message::SetEntityPosition& msg)
                        {
                                this->transform.setPosition(msg.entity, msg.position);
                        },
                        [this](const util::Message::MoveEntityBy& msg)
                        {
                                this->transform.moveBy(msg.entity, msg.displacement);
                        },
                        [this](const util::Message::SetEntityRotation& msg)
                        {
                                this->transform.setRotation(msg.entity, msg.rotation);
                        },
                        [this](const util::Message::RotateEntityBy& msg)
                        {
                                this->transform.rotateBy(msg.entity, msg.rotation);
                        },
                        [this](const util::Message::SetEntityScale& msg)
                        {
                                this->transform.setScale(msg.entity, msg.scale);
                        },
                        [this](const util::Message::ScaleEntityBy& msg)
                        {
                                this->transform.scaleBy(msg.entity, msg.scale);
                        },
                        [this](const util::Message::SetEntityVelocity& msg)
                        {
                                this->physics.setVelocity(msg.entity, msg.velocity);
                        },
                        [this](const util::Message::AccelerateEntityBy& msg)
                        {
                                this->physics.accelerateBy(msg.entity, msg.acceleration);
                        },
                        util::discardTheRest
                }, message.msg);
        }

private:

        entt::registry entities;
};

}