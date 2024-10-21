#pragma once

#include <Util/Math.hpp>

#include <cstdint>

namespace engine::physics
{

// Collider shapes.

using ColliderTag = uint32_t;

struct RectCollider
{
        util::FVector position;
        util::FVector halfSize;
        ColliderTag tag;
};

struct CircleCollider
{
        util::FVector position;
        float radius;
        ColliderTag tag;
};


// Detection.

struct Collision
{
        float penetration;
        util::FVector normal;

        bool occurred() const
        {
                return this->penetration > 0;
        }

        operator bool() const
        {
                return this->occurred();
        }
};

Collision collide(const CircleCollider circle1, const CircleCollider circle2);

Collision collide(const RectCollider rect1, const RectCollider rect2);

Collision collide(const RectCollider rect, const CircleCollider circle);

Collision collide(const CircleCollider circle, const RectCollider rect);

}
