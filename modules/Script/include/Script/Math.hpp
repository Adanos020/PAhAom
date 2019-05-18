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

        inline util::Vector tableToVector(const lua::Table& vec)
        {
                return util::Vector{vec["x"], vec["y"]};
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
                return {tableToVector(rect["position"]), tableToVector(rect["size"])};
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
inline lua::Retval lerpNumber(lua::Context& context)
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
inline lua::Retval normalizeNumber(lua::Context& context)
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
inline lua::Retval mapNumber(lua::Context& context)
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
 *      vec1 = Table. Presumably a vector.
 *      vec2 = Table. Presumably a vector.
 * 
 *  Returns: Boolean
 */
inline lua::Retval vectorsEqual(lua::Context& context)
{
        context.requireArgs<lua::Table, lua::Table>(2);
        return context.ret(impl::tableToVector(context.args[0]) == impl::tableToVector(context.args[1]));
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
        context.requireArgs<lua::Table, lua::Table, lua::Table>(3);
        const auto newVec = util::lerp(impl::tableToVector(context.args[0]),
                                       impl::tableToVector(context.args[1]),
                                       impl::tableToVector(context.args[2]));
        return context.ret(static_cast<lua::Valref>(impl::vectorToTable(newVec)));
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

/** Checks if given rectangles intersect.
 * 
 *  Params:
 *      rect1 = Table. Presumably a rectangle.
 *      rect2 = Table. Presumably a rectangle.
 * 
 *  Returns: Boolean
 */
inline lua::Retval rectanglesIntersect(lua::Context& context)
{
        context.requireArgs<lua::Table, lua::Table>(2);
        return context.ret(impl::toRectangle(context.args[0])
               .intersects(impl::toRectangle(context.args[1])));
}

/** Checks if given rectangle contains a point expressed by given vector.
 * 
 *  Params:
 *      rect = Table. Presumably a rectangle.
 *      vec  = Table. Presumably a vector.
 * 
 *  Returns: Boolean
 */
inline lua::Retval rectangleContains(lua::Context& context)
{
        context.requireArgs<lua::Table, lua::Table>(2);
        return context.ret(impl::toRectangle(context.args[0])
                .contains(impl::tableToVector(context.args[1])));
}

}