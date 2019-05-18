#pragma once


#include <Engine/ECS/Component.hpp>
#include <Engine/ECS/Entity.hpp>

#include <Util/Math.hpp>

#include <type_traits>


namespace engine::ecs
{

class PositionComponent : public Component, public util::Vector
{
public:

        PositionComponent(const util::Vector pos, Entity* const owner)
        : util::Vector(pos)
        {
                this->typeID = getComponentTypeID<PositionComponent>();
                this->owner = owner;
        }

        PositionComponent(const PositionComponent& copy)
        : util::Vector(copy)
        {
                this->owner = copy.owner;
        }

        virtual void update() override
        {
        }
};

}