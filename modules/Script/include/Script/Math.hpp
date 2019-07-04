#pragma once


#include <Script/Lua.hpp>
#include <Util/Math.hpp>

#include <SFML/Graphics/Rect.hpp>

#include <algorithm>
#include <cstdint>
#include <iostream>


namespace script
{

namespace impl
{
        inline static bool isVector(sol::table vec)
        {
                return vec["x"].get_type() == sol::type::number
                   and vec["y"].get_type() == sol::type::number;
        }

        inline static sol::table vectorToTable(const util::Vector vec)
        {
                return lua.create_table_with("x", vec.x, "y", vec.y);
        }

        inline static bool isRectangle(sol::table rect)
        {
                return rect["left"  ].get_type() == sol::type::number
                   and rect["top"   ].get_type() == sol::type::number
                   and rect["width" ].get_type() == sol::type::number
                   and rect["height"].get_type() == sol::type::number;
        }

        inline static sf::FloatRect toRectangle(sol::table rect)
        {
                if (isRectangle(rect))
                {
                        return {rect["left"], rect["top"], rect["width"], rect["height"]};
                }
                return {};
        }

        inline static sol::table rectangleToTable(const sf::FloatRect rect)
        {
                return lua.create_table_with(
                        "left",  rect.left,  "top",    rect.top,
                        "width", rect.width, "height", rect.height);
        }
}

/** Creates a new Vector out of given x and y coordinates.
 * 
 *  Params:
 *      x = Number.
 *      y = Number.
 * 
 *  Returns: Vector
 */
inline static sol::table vector(const float x, const float y)
{
        return lua.create_table_with("x", x, "y", y);
}

/** Checks if given table is an vector, i.e. it has two numbers called "x" and "y"
 *  ("x", "y", and "z", if it's 3D).
 * 
 *  Params:
 *      vec = Table.
 * 
 *  Returns: Boolean
 */
inline static bool isVector(sol::table vec)
{
        return impl::isVector(vec);
}

/** Checks if given vectors are equal.
 * 
 *  Params:
 *      vec1 = Vector.
 *      vec2 = Vector.
 * 
 *  Returns: Boolean
 */
inline static bool vectorEquals(sol::table vec1, sol::table vec2)
{
        return util::Vector{vec1} == util::Vector{vec2};
}

/** Adds two vectors to each other.
 * 
 *  Params:
 *      vec1 = Vector.
 *      vec2 = Vector.
 * 
 *  Returns: Vector
 */
inline static sol::table vectorAdd(sol::table vec1, sol::table vec2)
{
        const auto v1 = util::Vector{vec1};
        const auto v2 = util::Vector{vec2};
        return impl::vectorToTable(v1 + v2);
}

/** Subtracts two vectors from each other.
 * 
 *  Params:
 *      vec1 = Vector.
 *      vec2 = Vector.
 * 
 *  Returns: Vector
 */
inline static sol::table vectorSubtract(sol::table vec1, sol::table vec2)
{
        const util::Vector v1 = {vec1};
        const util::Vector v2 = {vec2};
        return impl::vectorToTable(v1 - v2);
}

/** Scales a vector by given factor.
 * 
 *  Params:
 *      vec = Vector.
 *      fac = Number.
 * 
 *  Returns: Vector
 */
inline static sol::table vectorMultiply(sol::table vec, const float fac)
{
        return impl::vectorToTable(util::Vector{vec} * fac);
}

/** Scales a vector by the inverse of given factor.
 * 
 *  Params:
 *      vec = Vector.
 *      fac = Number.
 * 
 *  Returns: Vector
 */
inline static sol::table vectorDivide(sol::table vec, const float fac)
{
        return impl::vectorToTable(util::Vector{vec} / fac);
}

/** Inverses the direction of given vector.
 * 
 *  Params:
 *      vec = Vector.
 * 
 *  Returns: Vector
 */
inline static sol::table vectorInverse(sol::table vec)
{
        return impl::vectorToTable(-util::Vector{vec});
}

/** Calculates the squared length of a vector.
 * 
 *  Params:
 *      vec = Vector.
 * 
 *  Returns: Number
 */
inline static float vectorLengthSquared(sol::table vec)
{
        return util::Vector{vec}.lengthSquared();
}

/** Calculates the length of a vector.
 * 
 *  Params:
 *      vec = Vector.
 * 
 *  Returns: Number
 */
inline static float vectorLength(sol::table vec)
{
        return util::Vector{vec}.length();
}

/** Creates a new vector with the same direction as the given vector but with a different length.
 * 
 *  Params:
 *      vec = Vector.
 *      len = Number.
 * 
 *  Returns: Vector
 */
inline static sol::table vectorSetLength(sol::table vec, const float len)
{
        return impl::vectorToTable(util::Vector{vec}.length(len));
}

/** Calculates the dot product of two vectors.
 * 
 *  Params:
 *      vec1 = Vector.
 *      vec2 = Vector.
 * 
 *  Returns: Number
 */
inline static float vectorDot(sol::table vec1, sol::table vec2)
{
        return util::Vector{vec1}.dot(vec2);
}

/** Limits a vector's length to a given `len`.
 * 
 *  Params:
 *      vec = Vector.
 *      len = Number. The length that the vector is limited to.
 * 
 *  Returns: Vector
 */
inline static sol::table vectorLimit(sol::table vec, const float len)
{
        return impl::vectorToTable(util::Vector{vec}.limit(len));
}

/** Calculates a unit vector out of an existing vector.
 * 
 *  Params:
 *      vec = Vector.
 * 
 *  Returns: Vector
 */
inline static sol::table vectorNormalize(sol::table vec)
{
        return impl::vectorToTable(util::Vector{vec}.normalize());
}

/** Limits a point (expressed by a Vector) to a given area (expressed by two Vectors).
 * 
 *  Params:
 *      vec = Vector. The given point.
 *      min = Vector. Top-left corner of the limited area.
 *      max = Vector. Bottom-right corner of the limited area.
 * 
 *  Returns: Vector
 */
inline static sol::table vectorClampToArea(sol::table vec, sol::table min, sol::table max)
{
        return impl::vectorToTable(util::Vector{vec}.clamp(util::Vector{min}, util::Vector{max}));
}

/** Limits a Vector's length to a given range (expressed by two Numbers).
 * 
 *  Params:
 *      vec = Vector. The given point.
 *      min = Number. Minimum length.
 *      max = Number. Maximum length.
 * 
 *  Returns: Vector
 */
inline static sol::table vectorClampToLength(sol::table vec, const float min, const float max)
{
        return impl::vectorToTable(util::Vector{vec}.clamp(min, max));
}

/** Linearly interpolates between two given vectors.
 * 
 *  Params:
 *      vec1  = Vector. Lower bounds.
 *      vec2  = Vector. Upper bounds.
 *      alpha = Vector. Alpha values - in range [0, 1].
 * 
 *  Returns: Vector
 */
inline static sol::table vectorLerp(sol::table vec1, sol::table vec2, const float alpha)
{
        return impl::vectorToTable(util::Vector::lerp(util::Vector{vec1}, util::Vector{vec2}, alpha));
}

/** Converts Polar coordinates of a point to Cartesian coordinates.
 * 
 *  Params:
 *      radius = Number. Distance from origin.
 *      angle  = Number. Angle in radians.
 * 
 *  Returns: Vector
 */
inline static sol::table vectorFromPolar(const float radius, const float angle)
{
        return impl::vectorToTable(util::Vector::fromPolar(radius, angle));
}

/** Calculates the angle between two vectors.
 * 
 *  Params:
 *      vec1 = Vector.
 *      vec2 = Vector.
 * 
 *  Returns: Number
 */
inline static float vectorAngleBetween(sol::table vec1, sol::table vec2)
{
        return util::Vector::angleBetween(util::Vector{vec1}, util::Vector{vec2});
}

/** Creates a new Rectangle out of given parameters.
 * 
 *  Params:
 *      left   = Number. X-coordinate of the left side.
 *      top    = Number. Y-coordinate of the top side.
 *      width  = Number.
 *      height = Number.
 *  Alternatively:
 *      position = Vector.
 *      size     = Vector.
 * 
 *  Returns: Rectangle
 */
inline static sol::table rectangle(const sol::variadic_args& args)
{
        if (args.size() == 2)
        {
                return impl::rectangleToTable(
                        {util::Vector{args[0].as<sol::table>()},
                         util::Vector{args[1].as<sol::table>()}});
        }
        else if (args.size() == 4)
        {
                return impl::rectangleToTable({args[0].as<float>(), args[1].as<float>(),
                                               args[2].as<float>(), args[3].as<float>()});
        }
        return impl::rectangleToTable({});
}

/** Checks if given table is a rectangle, i.e. it has two vectors called
 *  "position" and "size".
 * 
 *  Params:
 *      rect = Table.
 * 
 *  Returns: Boolean
 */
inline static bool isRectangle(sol::table rect)
{
        return impl::isRectangle(rect);
}

/** Checks if given rectangle contains a point expressed by given vector.
 * 
 *  Params:
 *      rect = Table. Presumably a rectangle.
 *      vec  = Vector.
 * 
 *  Returns: Boolean
 */
inline static bool rectangleContains(sol::table rect, sol::table vec)
{
        return impl::toRectangle(rect).contains(util::Vector{vec});
}

/** Checks if given rectangles intersect.
 * 
 *  Params:
 *      rect1 = Table. Presumably a rectangle.
 *      rect2 = Table. Presumably a rectangle.
 * 
 *  Returns: Boolean
 */
inline static bool rectangleIntersects(sol::table rect1, sol::table rect2)
{
        return impl::toRectangle(rect1).intersects(impl::toRectangle(rect2));
}

inline static void loadMath()
{
        lua["clamp"]     = std::clamp<double>;
        lua["iclamp"]    = std::clamp<std::int32_t>;
        lua["lerp"]      = util::lerp;
        lua["normalize"] = util::normalize;
        lua["map"]       = util::map;

        // lua.new_usertype<sf::Vector2f>("vector",
        //         "x", &sf::Vector2f::x,
        //         "y", &sf::Vector2f::y);

        lua.new_usertype<sf::Vector2i>("ivector",
                "x", &sf::Vector2i::x,
                "y", &sf::Vector2i::y);

        lua["vector"]   = vector;
        lua["isVector"] = isVector;

        sol::table vec;
        lua.create_named_table("vec",
                "equals",        vectorEquals,
                "add",           vectorAdd,
                "subtract",      vectorSubtract,
                "multiply",      vectorMultiply,
                "divide",        vectorDivide,
                "inverse",       vectorInverse,
                "lengthSquared", vectorLengthSquared,
                "length",        vectorLength,
                "setLength",     vectorSetLength,
                "limit",         vectorLimit,
                "normalize",     vectorNormalize,
                "clampToArea",   vectorClampToArea,
                "clampToLength", vectorClampToLength,
                "fromPolar",     vectorFromPolar,
                "dot",           vectorDot,
                "angleBetween",  vectorAngleBetween,
                "lerp",          vectorLerp);

        // lua.new_usertype<sf::FloatRect>("rectangle",
        //         "left",   &sf::FloatRect::left,
        //         "top",    &sf::FloatRect::top,
        //         "width",  &sf::FloatRect::width,
        //         "height", &sf::FloatRect::Height);
        lua["rectangle"] = rectangle;
        lua["isRectangle"] = isRectangle;
        lua.create_named_table("rect",
                "contains",   rectangleContains,
                "intersects", rectangleIntersects);
}

}