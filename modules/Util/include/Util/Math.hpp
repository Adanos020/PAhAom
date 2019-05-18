#pragma once


#include <Util/Types.hpp>

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>

#include <cmath>
#include <type_traits>


namespace util
{

// Numeric

inline float lerp(const float val1, const float val2, const float alpha)
{
        return (1.0 - alpha) * val1 + alpha * val2;
}

inline float normalize(const float val, const float lo, const float hi)
{
        return (val - lo) / (hi - lo);
}

inline float mapNumber(const float val, const float lo1, const float hi1,
                       const float lo2, const float hi2)
{
        return normalize(val, lo1, hi1) * (hi2 - lo2) + lo2;
}

// Vector

struct Vector : sf::Vector2f
{
        Vector(float x, float y)
        : sf::Vector2f(x, y)
        {
        }

        Vector(const Vector& copy)
        : sf::Vector2f(copy)
        {
        }

        static Vector fromPolar(const float radius, const float angle)
        {
                return {radius * std::cos(angle), radius * std::sin(angle)};
        }

        float lengthSquared() const
        {
                return this->x * this->x + this->y * this->y;
        }

        float length() const
        {
                return std::sqrt(this->lengthSquared());
        }

        Vector& length(const float l)
        {
                this->normalize();
                this->x *= l;
                this->y *= l;
                return *this;
        }

        Vector& normalize()
        {
                float l = this->length();
                this->x /= l;
                this->y /= l;
                return *this;
        }

        Vector& clamp(const Vector lo, const Vector hi)
        {
                this->x = std::clamp(this->x, lo.x, hi.x);
                this->y = std::clamp(this->y, lo.y, hi.y);
                return *this;
        }
};

inline Vector lerp(const Vector vec1, const Vector vec2, const Vector alpha)
{
        return {
                lerp(vec1.x, vec2.x, alpha.x),
                lerp(vec1.y, vec2.y, alpha.y),
        };
}

}