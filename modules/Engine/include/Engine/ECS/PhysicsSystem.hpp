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

        void assignCircleRB(const entt::entity entity, const util::Vector velocity,
                            const float mass, const float radius)
        {
                this->entities.assign<CircleRigidBody>(entity, velocity, mass, radius);
        }

        void assignCircleRB(const entt::entity entity, const lua::Table& entityTable)
        {
                if (entityTable["circleRB"].is<lua::Table>())
                {
                        lua::Table circleRB = entityTable["circleRB"];
                        this->assignCircleRB(entity,
                                script::tableFieldOr(circleRB, "velocity", util::Vector{}),
                                circleRB["mass"].to<float>(0),
                                circleRB["radius"].to<float>(0)
                        );
                }
        }

        void assignRectRB(const entt::entity entity, const util::Vector velocity,
                          const float mass, const util::Vector size)
        {
                this->entities.assign<RectRigidBody>(entity, velocity, mass, size);
        }

        void assignRectRB(const entt::entity entity, const lua::Table& entityTable)
        {
                if (entityTable["rectRB"].is<lua::Table>())
                {
                        lua::Table rectRB = entityTable["rectRB"];
                        this->assignRectRB(entity,
                                script::tableFieldOr(rectRB, "velocity", util::Vector{}),
                                rectRB["mass"].to<float>(0),
                                script::tableFieldOr(rectRB, "size", util::Vector{})
                        );
                }
        }

        void assignPhysics(const entt::entity entity, const lua::Table& entityTable)
        {
                this->assignCircleRB(entity, entityTable);
                this->assignRectRB(entity, entityTable);
        }

        void update()
        {
                auto handle = [&](const entt::entity, Transform& transform, auto& rb)
                {
                        transform.position += rb.velocity * util::FRAME_TIME.asSeconds();
                };

                entities.sort<Transform, CircleRigidBody>();
                entities.view<Transform, CircleRigidBody>().each(handle);

                entities.sort<Transform, RectRigidBody>();
                entities.view<Transform, RectRigidBody>().each(handle);
        }

private:

        entt::registry& entities;
};

}