#pragma once


#include <Engine/ECS/Component.hpp>
#include <Engine/ECS/Entity.hpp>

#include <SFML/System/Vector2.hpp>

#include <type_traits>


namespace engine::ecs
{

class PositionComponent : public Component, public sf::Vector2f
{
public:

        PositionComponent(const sf::Vector2f pos, Entity* const owner)
        : sf::Vector2f(pos)
        {
                this->typeID = getComponentTypeID<PositionComponent>();
                this->owner = owner;
        }

        PositionComponent(const PositionComponent& copy)
        {
                this->owner = copy.owner;
                this->x = copy.x;
                this->y = copy.y;
        }

        virtual void update() override
        {
        }
};

}