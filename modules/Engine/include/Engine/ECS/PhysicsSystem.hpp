#pragma once


#include <Engine/ECS/Components.hpp>

#include <Script/Math.hpp>

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

        void assignRigidBody(const entt::entity entity, const util::FVector velocity, const float mass)
        {
                this->entities.emplace<RigidBody>(entity, velocity, mass);
        }

        void assignRigidBody(const entt::entity entity, sol::table entityTable)
        {
                if (entityTable["rigidBody"].get_type() == sol::type::table)
                {
                        sol::table rigidBody = entityTable["rigidBody"];
                        auto defaultVelocity = util::FVector::Zero;
                        this->assignRigidBody(entity,
                                rigidBody["velocity"].get_or(defaultVelocity),
                                rigidBody["mass"].get_or(0.f));
                }
        }

        void assignPhysics(const entt::entity entity, sol::table entityTable)
        {
                this->assignRigidBody(entity, entityTable);
        }

        void setVelocity(const entt::entity entity, const util::FVector velocity)
        {
                this->entities.get<RigidBody>(entity).velocity = velocity;
        }

        void accelerateBy(const entt::entity entity, const util::FVector acceleration)
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