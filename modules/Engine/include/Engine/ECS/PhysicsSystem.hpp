#pragma once


#include <Engine/ECS/Components.hpp>

#include <Script/Aux.hpp>

#include <Util/Constants.hpp>
#include <Util/Observer.hpp>

#include <entt/entity/registry.hpp>


namespace engine::ecs
{

class PhysicsSystem : public util::Observer
{
public:

        PhysicsSystem(entt::registry& entities)
        : entities(entities)
        {
                util::Subject::addObserver(this);
        }

        ~PhysicsSystem()
        {
                util::Subject::deleteObserver(this);
        }

        void assignRigidBody(const entt::entity entity, const util::Vector velocity, const float mass)
        {
                this->entities.assign<RigidBody>(entity, velocity, mass);
        }

        void assignRigidBody(const entt::entity entity, const lua::Table& entityTable)
        {
                if (entityTable["rigidBody"].is<lua::Table>())
                {
                        lua::Table rigidBody = entityTable["rigidBody"];
                        this->assignRigidBody(entity,
                                script::tableFieldOr(rigidBody, "velocity", util::Vector{}),
                                rigidBody["mass"].to<float>(0));
                }
        }

        void assignPhysics(const entt::entity entity, const lua::Table& entityTable)
        {
                this->assignRigidBody(entity, entityTable);
        }

        void setVelocity(const entt::entity entity, const util::Vector velocity)
        {
                this->entities.get<RigidBody>(entity).velocity = velocity;
        }

        void accelerateBy(const entt::entity entity, const util::Vector acceleration)
        {
                this->entities.get<RigidBody>(entity).velocity += acceleration;
        }

        void setMass(const entt::entity entity, const float mass)
        {
                this->entities.get<RigidBody>(entity).mass = mass;
        }

        void update()
        {
                entities.sort<Transform, RigidBody>();
                entities.view<Transform, RigidBody>().each(
                        [&](const entt::entity, Transform& transform, const auto& rb)
                        {
                                transform.position += rb.velocity * util::FRAME_TIME.asSeconds();
                        });
        }

private:

        virtual void receive(const util::Message& message) override
        {
                std::visit(util::MsgHandlers {
                        [this](const util::Message::SetEntityVelocity& msg)
                        {
                                this->setVelocity(msg.entity, msg.velocity);
                        },
                        [this](const util::Message::AccelerateEntityBy& msg)
                        {
                                this->accelerateBy(msg.entity, msg.acceleration);
                        },
                        [this](const util::Message::SetEntityMass& msg)
                        {
                                this->setMass(msg.entity, msg.mass);
                        },
                        util::discardTheRest
                }, message.msg);
        }

private:

        entt::registry& entities;
};

}