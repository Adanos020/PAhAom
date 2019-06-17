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

        entt::entity create()
        {
                return this->entities.create();
        }

public:

        RenderSystem render;
        TransformSystem transform;

private:

        entt::registry entities;
};

}