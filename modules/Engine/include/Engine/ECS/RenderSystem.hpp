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

        void assignGraphics(const entt::entity entity, sol::table entityTable)
        {
                if (entityTable["graphics"].get_type() == sol::type::table)
                {
                        sol::table gfxTable = entityTable["graphics"];
                        if (auto gfx = script::tableToDrawable(gfxTable))
                        {
                                const auto z       = gfxTable.get_or("z", 0);
                                const auto visible = gfxTable.get_or("visible", true);
                                this->assignGraphics(entity, std::move(*gfx), z, visible);
                        }
                }
        }

        void drawTo(sf::RenderTarget& target)
        {
                // Ensure that the transforms be aligned with graphical components.
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