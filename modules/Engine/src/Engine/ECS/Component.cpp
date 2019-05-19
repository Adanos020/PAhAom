#include <Engine/ECS/Component.hpp>
#include <Engine/ECS/GraphicsComponent.hpp>
#include <Engine/ECS/PositionComponent.hpp>


namespace engine::ecs
{

std::unique_ptr<Component> Component::copy() const
{
        if (this->typeID == getComponentTypeID<GraphicsComponent>())
        {
                return std::make_unique<GraphicsComponent>(
                        reinterpret_cast<const GraphicsComponent&>(*this));
        }
        if (this->typeID == getComponentTypeID<PositionComponent>())
        {
                return std::make_unique<PositionComponent>(
                        reinterpret_cast<const PositionComponent&>(*this));
        }
        return nullptr;
}

}