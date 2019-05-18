#pragma once


#include <Engine/ECS/Component.hpp>
#include <Engine/ECS/Entity.hpp>
#include <Engine/ECS/PositionComponent.hpp>

#include <Util/Types.hpp>
#include <Util/Graphics/Graphical.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <memory>
#include <type_traits>


namespace engine::ecs
{

class GraphicsComponent : public Component
{
public:

        GraphicsComponent(std::unique_ptr<util::graphics::Graphical> graphicalObject, Entity* const owner)
        : graphicalObject(std::move(graphicalObject))
        {
                this->typeID = getComponentTypeID<GraphicsComponent>();
                this->owner = owner;
        }

        GraphicsComponent(const GraphicsComponent& copy)
        : GraphicsComponent(copy.graphicalObject->copy(), copy.owner)
        {
        }

        virtual void update() override
        {
                if (this->owner->hasComponent<PositionComponent>())
                {
                        this->graphicalObject->setPosition(this->owner->getComponent<PositionComponent>().value().get());
                }
        }

        void draw(sf::RenderTarget& target) const
        {
                target.draw(*graphicalObject);
        }

private:

        std::unique_ptr<util::graphics::Graphical> graphicalObject;
};

}