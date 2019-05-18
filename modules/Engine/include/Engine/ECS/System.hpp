#pragma once


#include <Engine/ECS/Entity.hpp>
#include <Engine/ECS/GraphicsComponent.hpp>

#include <vector>
#include <type_traits>


namespace engine::ecs
{

class System
{
public:

        void addEntity(const Entity& entity)
        {
                this->entities.push_back(std::move(entity));
        }

        void update()
        {
                for (Entity& entity : this->entities)
                {
                        entity.update();
                }
        }

        void draw(std::size_t index, sf::RenderTarget& target)
        {
                if (auto optGFX = entities[index].getComponent<GraphicsComponent>())
                {
                        optGFX.value().get().draw(target);
                }
        }

private:

        std::vector<Entity> entities;
};

}