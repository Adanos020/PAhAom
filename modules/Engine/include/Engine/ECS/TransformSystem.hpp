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

        void assignTransform(const entt::entity entity, const util::Vector position,
                             const util::Vector scale, const float rotation)
        {
                entities.assign<Transform>(entity, position, scale, rotation);
        }

        void assignTransform(const entt::entity entity, const lua::Table& entityTable)
        {
                const util::Vector position = script::hasOpt(entityTable, "position", util::Vector());
                const util::Vector scale = script::hasOpt(entityTable, "scale", util::Vector(1, 1));
                const float rotation = script::hasOpt(entityTable, "rotation", 0);
                this->assignTransform(entity, position, scale, rotation);
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