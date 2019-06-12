#pragma once


#include <Engine/ECS/Components.hpp>

#include <entt/entity/registry.hpp>


namespace engine::ecs
{

class TransformSystem
{
public:

        TransformSystem(entt::registry& entities)
        : entities(entities)
        {
        }
        
        void setPosition(const entt::entity entity, const util::Vector position)
        {
                entities.get<Transform>(entity).position = position;
        }

        void setRotation(const entt::entity entity, const float rotation)
        {
                entities.get<Transform>(entity).rotation = rotation;
        }

        void setScale(const entt::entity entity, const util::Vector scale)
        {
                entities.get<Transform>(entity).scale = scale;
        }

private:

        entt::registry& entities;
};

}