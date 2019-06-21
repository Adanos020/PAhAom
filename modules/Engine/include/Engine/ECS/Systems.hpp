#pragma once


#include <Engine/ECS/InputSystem.hpp>
#include <Engine/ECS/PhysicsSystem.hpp>
#include <Engine/ECS/RenderSystem.hpp>
#include <Engine/ECS/TransformSystem.hpp>

#include <entt/entity/registry.hpp>


namespace engine::ecs
{

class Systems
{
public:

        Systems()
        : physics(entities)
        , render(entities)
        , transform(entities)
        {
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

public:

        InputSystem input;
        PhysicsSystem physics;
        RenderSystem render;
        TransformSystem transform;

private:

        entt::registry entities;
};

}