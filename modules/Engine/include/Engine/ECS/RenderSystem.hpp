#pragma once


#include <Engine/ECS/Components.hpp>

#include <Script/Aux.hpp>
#include <Script/Graphics.hpp>

#include <entt/entity/registry.hpp>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


namespace engine::ecs
{

class RenderSystem
{
public:

        RenderSystem(entt::registry& entities)
        : entities(entities)
        {
        }

        void assignGraphics(entt::entity entity, std::unique_ptr<sf::Drawable>&& drawable,
                            const std::int32_t z, const bool visible)
        {
                this->entities.assign<Graphics>(entity, std::move(drawable), z, visible);
                this->entities.sort<Graphics>(
                        [](const Graphics& a, const Graphics& b) { return a.z < b.z; });
        }

        void assignGraphics(const entt::entity entity, const lua::Table& entityTable)
        {
                if (lua::Table gfxTable = entityTable["graphics"]; gfxTable.len())
                {
                        if (auto gfx = script::tableToDrawable(gfxTable))
                        {
                                const std::int32_t z = script::tableFieldOr(gfxTable, "z", 0);
                                const bool visible = script::tableFieldOr(gfxTable, "visible", true);
                                this->assignGraphics(entity, std::move(gfx.value()), z, visible);
                        }
                }
        }

        void drawTo(sf::RenderTarget& target)
        {
                this->entities.sort<Transform, Graphics>();
                this->entities.view<Graphics, Transform>().each(
                        [&target](entt::entity, const Graphics& gfx, const Transform& transform)
                        {
                                if (gfx.visible)
                                {
                                        sf::RenderStates states;
                                        states.transform.translate(transform.position);
                                        states.transform.rotate(transform.rotation);
                                        states.transform.scale(transform.scale);
                                        target.draw(*gfx.object, states);
                                }
                        });
        }

private:

        entt::registry& entities;
};

}