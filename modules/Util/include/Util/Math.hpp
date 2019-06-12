#pragma once


#include <Util/ErrorMessages.hpp>
#include <Util/Types.hpp>

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>

#include <luapp.hpp>

#include <cmath>
#include <type_traits>


namespace util
{

// Numeric

inline float lerp(const float val1, const float val2, const float alpha)
{
        return (1 - alpha) * val1 + alpha * val2;
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
        Vector(const float x = 0, const float y = 0)
        : sf::Vector2f(x, y)
        {
        }

        Vector(const Vector& copy)
        : sf::Vector2f(copy)
        {
        }

        template<typename T>
        Vector(const sf::Vector2<T>& other)
        : sf::Vector2f(other)
        {
                static_assert(std::is_arithmetic_v<T>, typeNotArithmetic);
        }

        Vector(const lua::Valref vec)
        : sf::Vector2f(vec["x"], vec["y"])
        {
        }

        float lengthSquared() const
        {
                return this->x * this->x + this->y * this->y;
        }

        float length() const
        {
                return std::sqrt(this->lengthSquared());
        }

        float dot(const Vector& rhs) const
        {
                return this->x * rhs.x + this->y * rhs.y;
        }

        Vector& length(const float l)
        {
                this->normalize();
                this->x *= l;
                this->y *= l;
                return *this;
        }

        Vector length(const float l) const
        {
                Vector v = *this;
                return v.length(l);
        }

        Vector& limit(const float l)
        {
                if (this->length() > l)
                {
                        this->length(l);
                }
                return *this;
        }

        Vector limit(const float l) const
        {
                Vector v = *this;
                return v.limit(l);
        }

        Vector& normalize()
        {
                const float l = this->length();
                this->x /= l;
                this->y /= l;
                return *this;
        }

        Vector normalize() const
        {
                Vector v = *this;
                return v.normalize();
        }

        Vector& clamp(const Vector& lo, const Vector& hi)
        {
                this->x = std::clamp(this->x, lo.x, hi.x);
                this->y = std::clamp(this->y, lo.y, hi.y);
                return *this;
        }

        Vector clamp(const Vector& lo, const Vector& hi) const
        {
                Vector v = *this;
                return v.clamp(lo, hi);
        }

        Vector& clamp(const float lo, const float hi)
        {
                if (this->length() > hi)
                {
                        this->length(hi);
                }
                else if (this->length() < lo)
                {
                        this->length(lo);
                }
                return *this;
        }

        Vector clamp(const float lo, const float hi) const
        {
                Vector v = *this;
                return v.clamp(lo, hi);
        }

public:

        static Vector fromPolar(const float radius, const float angle)
        {
                return {radius * std::cos(angle), radius * std::sin(angle)};
        }

        static Vector lerp(const Vector& vec1, const Vector& vec2, const float alpha)
        {
                return (1 - alpha) * vec1 + alpha * vec2;
        }

        static float angleBetween(const Vector& v1, const Vector& v2)
        {
                return std::acos(v1.dot(v2) / v1.length() / v2.length());
        }
};

}