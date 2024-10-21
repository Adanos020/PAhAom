#pragma once

#include <Script/Math.hpp>

#include <Util/Observer.hpp>

#include <entt/entity/registry.hpp>

namespace engine::ecs
{

class PhysicsSystem : public util::Observer
{
public:
        PhysicsSystem(entt::registry& entities);
        ~PhysicsSystem();

        void assignRigidBody(const entt::entity entity, const util::FVector velocity, const float mass);
        void assignRigidBody(const entt::entity entity, sol::table entityTable);
        void assignPhysics(const entt::entity entity, sol::table entityTable);
        void setVelocity(const entt::entity entity, const util::FVector velocity);
        void accelerateBy(const entt::entity entity, const util::FVector acceleration);
        void setMass(const entt::entity entity, const float mass);
        void update();

private:
        virtual void receive(const util::Message& message) override;

private:

        entt::registry& entities;
};

}
