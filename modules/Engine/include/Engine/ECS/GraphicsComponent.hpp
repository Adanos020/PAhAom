#pragma once


#include <Engine/ECS/Component.hpp>
#include <Engine/ECS/Entity.hpp>
#include <Engine/ECS/PositionComponent.hpp>

#include <Util/Types.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <memory>
#include <type_traits>


namespace engine::ecs
{

class Graphics2DComponent : public Component
{
public:

        Graphics2DComponent(std::unique_ptr<sf::Drawable> graphicalObject, Entity* const owner)
        : graphicalObject(std::move(graphicalObject))
        {
                this->typeID = getComponentTypeID<Graphics2DComponent>();
                this->owner = owner;
        }

        Graphics2DComponent(const Graphics2DComponent& copy)
        {

        }

        virtual void update() override
        {
                if (this->owner->hasComponent<PositionComponent<sf::Vector2f>>())
                {
                        auto transformable = reinterpret_cast<sf::Transformable*>(graphicalObject.get());
                        transformable->setPosition(this->owner->getComponent<PositionComponent<sf::Vector2f>>().value().get());
                }
        }

        void draw(sf::RenderTarget& target) const
        {
                target.draw(*graphicalObject);
        }

private:

        std::unique_ptr<sf::Drawable> graphicalObject;
};

}