#pragma once


#include <Engine/ECS/Component.hpp>
#include <Engine/ECS/Entity.hpp>

#include <Util/Types.hpp>

#include <type_traits>


namespace engine::ecs
{

template<class VectorType>
class PositionComponent : public Component, public VectorType
{
        static_assert(util::isVectorType<VectorType>);

public:

        PositionComponent(const VectorType pos, Entity* const owner)
        : VectorType(pos)
        {
                this->typeID = getComponentTypeID<PositionComponent>();
                this->owner = owner;
        }

        PositionComponent(const PositionComponent& copy)
        {
                this->owner = copy.owner;
                this->x = copy.x;
                this->y = copy.y;
                if constexpr (std::is_same_v<VectorType, sf::Vector3f>)
                {
                        this->z = copy.z;
                }
        }

        virtual void update() override {}
};

}