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

        if (!table["graphics2D"].is<lua::Nil>())
        {
                lua::Table drawable = table["graphics2D"];
                if (auto graphicalObject = tableToDrawable(drawable))
                {
                        entity.addComponent<Graphics2DComponent>(std::move(graphicalObject.value()));
                }
        }

        if (!table["position"].is<lua::Nil>())
        {
                lua::Table pos = table["position"];
                if (impl::isVector<2>(pos))
                {
                        entity.addComponent<PositionComponent<sf::Vector2f>>(impl::toVector<2>(pos));
                }
                else if (impl::isVector<3>(pos))
                {
                        entity.addComponent<PositionComponent<sf::Vector3f>>(impl::toVector<3>(pos));
                }
        }

        return entity;
}

}