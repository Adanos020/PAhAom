#pragma once

#include <entt/entity/registry.hpp>

#include <Script/Lua.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

namespace engine::ecs
{

class RenderSystem
{
public:
        RenderSystem(entt::registry& entities);

        void assignGraphics(entt::entity entity, std::unique_ptr<sf::Drawable>&& drawable,
                            const int32_t z, const bool visible);
        void assignGraphics(const entt::entity entity, sol::table entityTable);
        void drawTo(sf::RenderTarget& target);

private:
        entt::registry& entities;
};

}
