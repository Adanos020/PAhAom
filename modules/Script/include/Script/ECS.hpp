#pragma once


#include <Engine/ECS/Components.hpp>

#include <Script/Aux.hpp>
#include <Script/Graphics.hpp>

#include <entt/entity/registry.hpp>

#include <luapp.hpp>


namespace script
{

inline static void assignTransform(entt::registry& entities, const entt::entity entity, const lua::Table& entityTable)
{
        const util::Vector position = script::hasOpt(entityTable, "position", util::Vector());
        const util::Vector scale = script::hasOpt(entityTable, "scale", util::Vector(1, 1));
        const float rotation = script::hasOpt(entityTable, "rotation", 0);
        entities.assign<engine::ecs::Transform>(entity, position, scale, rotation);
}

inline static void assignGraphics(entt::registry& entities, const entt::entity entity, const lua::Table& entityTable)
{
        if (lua::Table gfxTable = entityTable["graphics"]; gfxTable.len())
        {
                if (auto gfx = script::tableToDrawable(gfxTable))
                {
                        const std::int32_t z = script::hasOpt(gfxTable, "z", 0);
                        const bool visible = script::hasOpt(gfxTable, "visible", true);
                        entities.assign<engine::ecs::Graphics>(entity, std::move(gfx.value()), z, visible);
                }
        }
        entities.sort<engine::ecs::Graphics>(
                [](const engine::ecs::Graphics& a, const engine::ecs::Graphics& b) { return a.z < b.z; });
}

inline static void addEntity(entt::registry& entities, const lua::Table& entityTable)
{
        const entt::entity entity = entities.create();
        assignTransform(entities, entity, entityTable);
        assignGraphics(entities, entity, entityTable);
}

}