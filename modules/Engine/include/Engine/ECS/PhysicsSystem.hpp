#pragma once


#include <Engine/ECS/Components.hpp>

#include <Script/Aux.hpp>

#include <Util/Constants.hpp>

#include <entt/entity/registry.hpp>


namespace engine::ecs
{

class PhysicsSystem
{
public:

        PhysicsSystem(entt::registry& entities)
        : entities(entities)
        {
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

        void addMass(const entt::entity entity, const float dMass)
        {
                this->entities.get<RigidBody>(entity).mass += dMass;
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

        entt::registry& entities;
};

}