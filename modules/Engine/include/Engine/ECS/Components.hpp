#pragma once


#include <Util/Math.hpp>

#include <SFML/Graphics/Drawable.hpp>

#include <cstdint>
#include <memory>


namespace engine::ecs
{

// Shared components

struct Transform
{
        util::Vector position;
        util::Vector scale;
        float rotation;
};


// Graphical components

struct Graphics
{
        std::unique_ptr<sf::Drawable> object;
        std::int32_t z;
        bool visible;
};


// Physical components

struct BasicRigidBody
{
        util::Vector velocity;
        float mass;
};

struct CircleRigidBody : BasicRigidBody
{
        float radius;
};

struct RectRigidBody : BasicRigidBody
{
        util::Vector halfSize;
};

}