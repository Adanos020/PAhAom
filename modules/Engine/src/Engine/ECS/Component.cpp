#include <Engine/ECS/Component.hpp>
#include <Engine/ECS/GraphicsComponent.hpp>
#include <Engine/ECS/PositionComponent.hpp>


namespace engine::ecs
{

std::unique_ptr<Component> Component::copy() const
{
        if (this->typeID == getComponentTypeID<Graphics2DComponent>())
        {
                return std::make_unique<Graphics2DComponent>(
                        *reinterpret_cast<const Graphics2DComponent*>(this));
        }
        if (this->typeID == getComponentTypeID<PositionComponent<sf::Vector2f>>())
        {
                return std::make_unique<PositionComponent<sf::Vector2f>>(
                        *reinterpret_cast<const PositionComponent<sf::Vector2f>*>(this));
        }
        if (this->typeID == getComponentTypeID<PositionComponent<sf::Vector3f>>())
        {
                return std::make_unique<PositionComponent<sf::Vector3f>>(
                        *reinterpret_cast<const PositionComponent<sf::Vector3f>*>(this));
        }
        return nullptr;
}

}