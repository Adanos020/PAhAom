#pragma once


#include <Engine/ECS/Components.hpp>
#include <Engine/ECS/Systems.hpp>

#include <Script/Aux.hpp>
#include <Script/Graphics.hpp>

#include <luapp.hpp>


namespace engine::ecs
{

// Entity creation

inline static void assignTransform(Systems& systems, const entt::entity entity,
                                   const lua::Table& entityTable)
{
        const util::Vector position = script::hasOpt(entityTable, "position", util::Vector());
        const util::Vector scale = script::hasOpt(entityTable, "scale", util::Vector(1, 1));
        const float rotation = script::hasOpt(entityTable, "rotation", 0);
        systems.transform.assignTransform(entity, position, scale, rotation);
}

inline static void assignGraphics(Systems& systems, const entt::entity entity,
                                  const lua::Table& entityTable)
{
        if (lua::Table gfxTable = entityTable["graphics"]; gfxTable.len())
        {
                if (auto gfx = script::tableToDrawable(gfxTable))
                {
                        const std::int32_t z = script::hasOpt(gfxTable, "z", 0);
                        const bool visible = script::hasOpt(gfxTable, "visible", true);
                        systems.render.addGraphics(entity, std::move(gfx.value()), z, visible);
                }
        }
}

inline static void addEntity(Systems& systems, lua::Table& entityTable)
{
        const entt::entity entity = systems.create();
        entityTable["id"] = entity;

        assignTransform(systems, entity, entityTable);
        assignGraphics(systems, entity, entityTable);
}

}