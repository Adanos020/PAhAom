#pragma once


#include <Engine/ECS/RenderSystem.hpp>
#include <Engine/ECS/TransformSystem.hpp>

#include <entt/entity/registry.hpp>


namespace engine::ecs
{

class Systems
{
public:

        Systems()
        : render(entities)
        , transform(entities)
        {
        }

        void addEntity(lua::Table& entityTable)
        {
                const entt::entity entity = this->entities.create();
                entityTable["id"] = entity;

                this->transform.assignTransform(entity, entityTable);
                this->render.assignGraphics(entity, entityTable);
        }

public:

        RenderSystem render;
        TransformSystem transform;

private:

        entt::registry entities;
};

}