#pragma once


#include <Script/Lua.hpp>
#include <Util/Math.hpp>

#include <SFML/Graphics/Rect.hpp>

#include <algorithm>


namespace script
{

namespace impl
{
        inline bool isVector(const lua::Table& vec)
        {
                return vec["x"].is<float>() and vec["y"].is<float>();
        }

        inline util::Vector tableToVector(const lua::Table vec)
        {
                return util::Vector(vec);
        }

        inline lua::Table vectorToTable(const util::Vector vec)
        {
                auto newVec = lua::Table{luaContext};
                newVec["x"] = vec.x;
                newVec["y"] = vec.y;
                return newVec;
        }

        inline bool isRectangle(const lua::Table& rect)
        {
                return isVector(rect["position"]) and isVector(rect["size"]);
        }

        inline sf::FloatRect toRectangle(const lua::Table& rect)
        {
                return {impl::tableToVector(rect["position"]), impl::tableToVector(rect["size"])};
        }
}

/** Returns the given number 'trimmed' to fit in a given range.
 * 
 *  Params:
 *      val = Number. It will be returned if it's between lo and hi
 *      lo  = Number. It will be returned if val is less than it.
 *      hi  = Number. It will be returned if val is greater than it.
 * 
 *  Returns: Number
 */
inline lua::Retval clamp(lua::Context& context)
{
        context.requireArgs<float, float, float>(3);

        const lua::Valref val = context.args[0];
        const lua::Valref lo  = context.args[1];
        const lua::Valref hi  = context.args[2];

        if (val.isInteger() and lo.isInteger() and hi.isInteger())
        {
                return context.ret(std::clamp(val.to<int>(), lo.to<int>(), hi.to<int>()));
        }
        return context.ret(std::clamp(val.to<float>(), lo.to<float>(), hi.to<float>()));
}

/** Linearly interpolates between two given values.
 * 
 *  Params:
 *      v1    = Number. Lower bound.
 *      v2    = Number. Upper bound.
 *      alpha = Number. Alpha value - in range [0, 1].
 * 
 *  Returns: Number
 */
inline lua::Retval numberLerp(lua::Context& context)
{
        context.requireArgs<float, float, float>(3);
        return context.ret(util::lerp(context.args[0].to<float>(),
                                      context.args[1].to<float>(),
                                      context.args[2].to<float>()));
}

/** Maps a number in given range from hi to lo into a value in range from 0 to 1.
 * 
 *  Params:
 *      val = Number. Value to map.
 *      hi  = Number. Lower bound of the original range.
 *      lo  = Number. Upper bound of the original range.
 * 
 *  Returns: Number - Mapped to range [0, 1]
 */
inline lua::Retval numberNormalize(lua::Context& context)
{
        context.requireArgs<float, float, float>(3);
        return context.ret(util::normalize(context.args[0], context.args[1], context.args[2]));
}

/** Maps a number in given range from hi to lo into a value in range from 0 to 1.
 * 
 *  Params:
 *      val = Number. Value to map.
 *      hi1  = Number. Lower bound of the original range.
 *      lo1  = Number. Upper bound of the original range.
 *      hi2  = Number. Lower bound of the target range.
 *      lo2  = Number. Upper bound of the target range.
 * 
 *  Returns: Number - Mapped to range [lo2, hi2]
 */
inline lua::Retval numberMap(lua::Context& context)
{
        context.requireArgs<float, float, float, float, float>(5);
        return context.ret(util::mapNumber(context.args[0], context.args[1], context.args[2],
                                           context.args[3], context.args[4]));
}

/** Checks if given table is an vector, i.e. it has two numbers called "x" and "y"
 *  ("x", "y", and "z", if it's 3D).
 * 
 *  Params:
 *      vec = Table.
 * 
 *  Returns: Boolean
 */
inline lua::Retval isVector(lua::Context& context)
{
        context.requireArgs<lua::Table>(1);
        return context.ret(impl::isVector(context.args[0]));
}

/** Checks if given vectors are equal.
 * 
 *  Params:
 *      vec1 = Vector.
 *      vec2 = Vector.
 * 
 *  Returns: Boolean
 */
inline lua::Retval vectorEquals(lua::Context& context)
{
        context.requireArgs<lua::Table, lua::Table>(2);
        return context.ret(impl::tableToVector(context.args[0]) == impl::tableToVector(context.args[1]));
}

/** Adds two vectors to each other.
 * 
 *  Params:
 *      vec1 = Vector.
 *      vec2 = Vector.
 * 
 *  Returns: Vector
 */
inline lua::Retval vectorAdd(lua::Context& context)
{
        context.requireArgs<lua::Table, lua::Table>(2);
        const util::Vector v1{lua::Table(context.args[0])};
        const util::Vector v2{lua::Table(context.args[1])};
        return context.ret(static_cast<lua::Valref>(impl::vectorToTable(v1 + v2)));
}

/** Subtracts two vectors from each other.
 * 
 *  Params:
 *      vec1 = Vector.
 *      vec2 = Vector.
 * 
 *  Returns: Vector
 */
inline lua::Retval vectorSubtract(lua::Context& context)
{
        context.requireArgs<lua::Table, lua::Table>(2);
        const util::Vector v1{lua::Table(context.args[0])};
        const util::Vector v2{lua::Table(context.args[1])};
        return context.ret(static_cast<lua::Valref>(impl::vectorToTable(v1 - v2)));
}

/** Scales a vector by given factor.
 * 
 *  Params:
 *      vec = Vector.
 *      fac = Number.
 * 
 *  Returns: Vector
 */
inline lua::Retval vectorMultiply(lua::Context& context)
{
        context.requireArgs<lua::Table, float>(2);
        const util::Vector v{lua::Table(context.args[0])};
        const float f = context.args[1];
        return context.ret(static_cast<lua::Valref>(impl::vectorToTable(v * f)));
}

/** Scales a vector by the inverse of given factor.
 * 
 *  Params:
 *      vec = Vector.
 *      fac = Number.
 * 
 *  Returns: Vector
 */
inline lua::Retval vectorDivide(lua::Context& context)
{
        context.requireArgs<lua::Table, float>(2);
        const util::Vector v{lua::Table(context.args[0])};
        const float f = context.args[1];
        return context.ret(static_cast<lua::Valref>(impl::vectorToTable(v / f)));
}

/** Inverses the direction of given vector.
 * 
 *  Params:
 *      vec = Vector.
 * 
 *  Returns: Vector
 */
inline lua::Retval vectorInverse(lua::Context& context)
{
        context.requireArgs<lua::Table>(1);
        const util::Vector v{lua::Table(context.args[0])};
        return context.ret(static_cast<lua::Valref>(impl::vectorToTable(-v)));
}

/** Calculates the squared length of a vector.
 * 
 *  Params:
 *      vec = Vector.
 * 
 *  Returns: Number
 */
inline lua::Retval vectorLengthSquared(lua::Context& context)
{
        context.requireArgs<lua::Table>(1);
        return context.ret(impl::tableToVector(context.args[0]).lengthSquared());
}

/** Calculates the length of a vector.
 * 
 *  Params:
 *      vec = Vector.
 * 
 *  Returns: Number
 */
inline lua::Retval vectorLength(lua::Context& context)
{
        context.requireArgs<lua::Table>(1);
        return context.ret(impl::tableToVector(context.args[0]).length());
}

/** Creates a new vector with the same direction as the given vector but with a different length.
 * 
 *  Params:
 *      vec    = Vector.
 *      length = Number.
 * 
 *  Returns: Vector
 */
inline lua::Retval vectorSetLength(lua::Context& context)
{
        context.requireArgs<lua::Table, float>(2);
        const auto newVec = impl::tableToVector(context.args[0]).length(context.args[1]);
        return context.ret(static_cast<lua::Valref>(impl::vectorToTable(newVec)));
}

/** Calculates the dot product of two vectors.
 * 
 *  Params:
 *      vec1 = Vector.
 *      vec2 = Vector.
 * 
 *  Returns: Number
 */
inline lua::Retval vectorDot(lua::Context& context)
{
        context.requireArgs<lua::Table, lua::Table>(2);
        return context.ret(impl::tableToVector(context.args[0]).dot(impl::tableToVector(context.args[1])));
}

/** Limits a vector's length to a given `len`.
 * 
 *  Params:
 *      vec = Vector.
 *      len = Number. The length that the vector is limited to.
 * 
 *  Returns: Vector
 */
inline lua::Retval vectorLimit(lua::Context& context)
{
        context.requireArgs<lua::Table, float>(2);
        const auto newVec = impl::tableToVector(context.args[0]).limit(context.args[1]);
        return context.ret(static_cast<lua::Valref>(impl::vectorToTable(newVec)));
}

/** Calculates a unit vector out of an existing vector.
 * 
 *  Params:
 *      vec = Vector.
 * 
 *  Returns: Vector
 */
inline lua::Retval vectorNormalize(lua::Context& context)
{
        context.requireArgs<lua::Table>(1);
        const auto newVec = impl::tableToVector(context.args[0]).normalize();
        return context.ret(static_cast<lua::Valref>(impl::vectorToTable(newVec)));
}

/** Limits a point (expressed by a Vector) to a given area (expressed by two Vectors).
 * 
 *  Params:
 *      point = Vector. The given point.
 *      min   = Vector. Top-left corner of the limited area.
 *      max   = Vector. Bottom-right corner of the limited area.
 * 
 *  Returns: Vector
 */
inline lua::Retval vectorClampToArea(lua::Context& context)
{
        context.requireArgs<lua::Table, lua::Table, lua::Table>(3);
        const auto newVec = impl::tableToVector(context.args[0]).clamp(
                impl::tableToVector(context.args[1]),
                impl::tableToVector(context.args[2])
        );
        return context.ret(static_cast<lua::Valref>(impl::vectorToTable(newVec)));
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
inline lua::Retval vectorClampToLength(lua::Context& context)
{
        context.requireArgs<lua::Table, float, float>(3);
        const auto newVec = impl::tableToVector(context.args[0]).clamp(
                float(context.args[1]),
                float(context.args[2])
        );
        return context.ret(static_cast<lua::Valref>(impl::vectorToTable(newVec)));
}

/** Linearly interpolates between two given vectors.
 * 
 *  Params:
 *      v1    = Vector. Lower bounds.
 *      v2    = Vector. Upper bounds.
 *      alpha = Vector. Alpha values - in range [0, 1].
 * 
 *  Returns: Number
 */
inline lua::Retval vectorLerp(lua::Context& context)
{
        context.requireArgs<lua::Table, lua::Table, float>(3);
        const auto newVec = util::Vector::lerp(
                impl::tableToVector(context.args[0]),
                impl::tableToVector(context.args[1]),
                context.args[2]);
        return context.ret(static_cast<lua::Valref>(impl::vectorToTable(newVec)));
}

/** Converts Polar coordinates of a point to Cartesian coordinates.
 * 
 *  Params:
 *      radius = Number. Distance from origin.
 *      angle  = Number. Angle in radians.
 * 
 *  Returns: Vector
 */
inline lua::Retval vectorFromPolar(lua::Context& context)
{
        context.requireArgs<float, float>(2);
        const auto newVec = util::Vector::fromPolar(context.args[0], context.args[1]);
        return context.ret(static_cast<lua::Valref>(impl::vectorToTable(newVec)));
}

/** Calculates the angle between two vectors.
 * 
 *  Params:
 *      vec1 = Vector.
 *      vec2 = Vector.
 * 
 *  Returns: Number
 */
inline lua::Retval vectorAngleBetween(lua::Context& context)
{
        context.requireArgs<lua::Table, lua::Table>(2);
        const auto newVec = util::Vector::angleBetween(
                impl::tableToVector(context.args[0]),
                impl::tableToVector(context.args[1])
        );
        return context.ret(static_cast<lua::Valref>(impl::vectorToTable(newVec)));
}

/** Checks if given table is a rectangle, i.e. it has two vectors called
 *  "position" and "size".
 * 
 *  Params:
 *      vec = Table.
 * 
 *  Returns: Boolean
 */
inline lua::Retval isRectangle(lua::Context& context)
{
        context.requireArgs<lua::Table>(1);
        return context.ret(impl::isRectangle(context.args[0]));
}

/** Checks if given rectangle contains a point expressed by given vector.
 * 
 *  Params:
 *      rect = Table. Presumably a rectangle.
 *      vec  = Vector.
 * 
 *  Returns: Boolean
 */
inline lua::Retval rectangleContains(lua::Context& context)
{
        context.requireArgs<lua::Table, lua::Table>(2);
        return context.ret(impl::toRectangle(context.args[0])
                .contains(impl::tableToVector(context.args[1])));
}

/** Checks if given rectangles intersect.
 * 
 *  Params:
 *      rect1 = Table. Presumably a rectangle.
 *      rect2 = Table. Presumably a rectangle.
 * 
 *  Returns: Boolean
 */
inline lua::Retval rectangleIntersects(lua::Context& context)
{
        context.requireArgs<lua::Table, lua::Table>(2);
        return context.ret(impl::toRectangle(context.args[0])
               .intersects(impl::toRectangle(context.args[1])));
}

}