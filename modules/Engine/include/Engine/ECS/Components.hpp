#pragma once


#include <Util/Math.hpp>

#include <SFML/Graphics/Drawable.hpp>

#include <luapp.hpp>

#include <cstdint>
#include <memory>


namespace engine::ecs
{

// Shared components

struct Transform
{
        util::Vector position = {0, 0};
        util::Vector scale = {1, 1};
        float rotation = 0;
};

// Graphical components

struct Graphics
{
        std::unique_ptr<sf::Drawable> object;
        std::int32_t z = 0;
        bool visible = true;
};


// Physical components

struct RigidBody
{
        util::Vector velocity = {0, 0};
        float mass = 0;
};

struct CircleCollider
{
        float radius = 0;
};

struct RectCollider
{
        util::Vector size = {0, 0};
};

}