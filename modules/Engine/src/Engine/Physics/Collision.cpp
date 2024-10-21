#include <Engine/Physics/Collision.hpp>

namespace engine::physics
{

Collision collide(const CircleCollider circle1, const CircleCollider circle2)
{
        const util::FVector displacement = circle2.position - circle1.position;
        return {displacement.length() - circle1.radius - circle2.radius, displacement.normalize()};
}

Collision collide(const RectCollider rect1, const RectCollider rect2)
{
        const float inTop    = std::min(rect1.position.y + rect1.halfSize.y, rect2.position.y + rect2.halfSize.y);
        const float inLeft   = std::min(rect1.position.x + rect1.halfSize.x, rect2.position.x + rect2.halfSize.x);
        const float inBottom = std::max(rect1.position.y - rect1.halfSize.y, rect2.position.y - rect2.halfSize.y);
        const float inRight  = std::max(rect1.position.x - rect1.halfSize.x, rect2.position.x - rect2.halfSize.x);

        // No collision?
        if (inLeft > inRight && inTop > inBottom)
        {
                return {0, {}};
        }
        return {
                util::FVector(inRight - inLeft, inBottom - inTop).length(),
                util::FVector(rect2.position - rect1.position).normalize()
        };
}

Collision collide(const RectCollider rect, const CircleCollider circle)
{
        const util::FVector closestPoint = circle.position.clamp(
                rect.position - rect.halfSize, rect.position + rect.halfSize);
        return {
                circle.radius - util::FVector(circle.position - closestPoint).length(),
                util::FVector(circle.position - rect.position).normalize()
        };
}

Collision collide(const CircleCollider circle, const RectCollider rect)
{
        Collision col = collide(rect, circle);
        col.normal = -col.normal;
        return col;
}

}
