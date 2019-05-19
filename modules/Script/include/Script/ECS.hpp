#pragma once


#include <Engine/ECS/Component.hpp>
#include <Engine/ECS/Entity.hpp>
#include <Engine/ECS/GraphicsComponent.hpp>
#include <Engine/ECS/PositionComponent.hpp>

#include <Script/Lua.hpp>
#include <Script/Math.hpp>
#include <Script/Graphics.hpp>


namespace script
{

inline engine::ecs::Entity tableToEntity(const lua::Table& table)
{
        using namespace engine::ecs;

        Entity entity;

        if (!table["graphics"].is<lua::Nil>())
        {
                lua::Table drawable = table["graphics"];
                if (auto graphicalObject = tableToDrawable(drawable))
                {
                        entity.addComponent<GraphicsComponent>(std::move(graphicalObject.value()));
                }
        }

        if (!table["position"].is<lua::Nil>())
        {
                lua::Table pos = table["position"];
                if (impl::isVector(pos))
                {
                        entity.addComponent<PositionComponent>(impl::tableToVector(pos));
                }
        }

        return entity;
}

}