#pragma once


#include <Script/Lua.hpp>
#include <Util/Math.hpp>

#include <SFML/Graphics/Rect.hpp>

#include <algorithm>


namespace script
{

namespace impl
{
        template<class Type>
        static constexpr bool isVectorType =
                std::is_same_v<Type, sf::Vector2f> or std::is_same_v<Type, sf::Vector3f>;

        template<size_t dimensions>
        static constexpr bool isSupportedDimensionCount =
                dimensions == 2 or dimensions == 3;

        template<size_t dimensions>
        inline bool isVector(const lua::Table& vec)
        {
                static_assert(isSupportedDimensionCount<dimensions>);

                if constexpr (dimensions == 2)
                {
                        return vec["x"].is<double>() and vec["y"].is<double>() and not vec["z"].is<double>();
                }
                else // 3D
                {
                        return vec["x"].is<double>() and vec["y"].is<double>() and vec["z"].is<double>();
                }
        }

        template<size_t dimensions>
        inline auto toVector(const lua::Table& vec)
        {
                static_assert(isSupportedDimensionCount<dimensions>);

                if constexpr (dimensions == 2)
                {
                        return sf::Vector2f{vec["x"], vec["y"]};
                }
                else // 3D
                {
                        return sf::Vector3f{vec["x"], vec["y"], vec["z"]};
                }
        }

        template<class VectorType>
        inline lua::Table vectorToTable(const VectorType vec)
        {
                static_assert(isVectorType<VectorType>);
                
                auto newVec = lua::Table{luaContext};
                newVec["x"] = vec.x;
                newVec["y"] = vec.y;
                if constexpr (std::is_same_v<VectorType, sf::Vector3f>)
                {
                        newVec["z"] = vec.z;
                }
                
                return newVec;
        }

        inline bool isRectangle(const lua::Table& rect)
        {
                return isVector<2>(rect["position"]) and isVector<2>(rect["size"]);
        }

        inline sf::FloatRect toRectangle(const lua::Table& rect)
        {
                return {toVector<2>(rect["position"]), toVector<2>(rect["size"])};
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
        context.requireArgs<double, double, double>(3);

        const lua::Valref val = context.args[0];
        const lua::Valref lo  = context.args[1];
        const lua::Valref hi  = context.args[2];

        if (val.isInteger() and lo.isInteger() and hi.isInteger())
        {
                return context.ret(std::clamp(val.to<int>(), lo.to<int>(), hi.to<int>()));
        }
        return context.ret(std::clamp(val.to<double>(), lo.to<double>(), hi.to<double>()));
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
        context.requireArgs<double, double, double>(3);
        return context.ret(util::lerp(context.args[0].to<double>(),
                                      context.args[1].to<double>(),
                                      context.args[2].to<double>()));
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
        context.requireArgs<double, double, double>(3);
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
        context.requireArgs<double, double, double, double, double>(5);
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
template<size_t dimensions>
inline lua::Retval isVector(lua::Context& context)
{
        context.requireArgs<lua::Table>(1);
        return context.ret(impl::isVector<dimensions>(context.args[0]));
}

/** Checks if given vectors are equal.
 * 
 *  Params:
 *      vec1 = Table. Presumably a vector.
 *      vec2 = Table. Presumably a vector.
 * 
 *  Returns: Boolean
 */
template<size_t dimensions>
inline lua::Retval vectorsEqual(lua::Context& context)
{
        context.requireArgs<lua::Table, lua::Table>(2);
        return context.ret(impl::toVector<dimensions>(context.args[0]) == impl::toVector<dimensions>(context.args[1]));
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
template<size_t dimensions>
inline lua::Retval vectorLerp(lua::Context& context)
{
        context.requireArgs<lua::Table, lua::Table, lua::Table>(3);
        const auto newVec = util::lerp(impl::toVector<dimensions>(context.args[0]),
                                       impl::toVector<dimensions>(context.args[1]),
                                       impl::toVector<dimensions>(context.args[2]));
        return context.ret(static_cast<lua::Valref>(impl::vectorToTable(newVec)));
}

/** Calculates the squared length of a vector.
 * 
 *  Params:
 *      vec = Vector.
 * 
 *  Returns: Number
 */
template<size_t dimensions>
inline lua::Retval vectorLengthSquared(lua::Context& context)
{
        context.requireArgs<lua::Table>(1);
        return context.ret(util::vecLengthSquared(impl::toVector<dimensions>(context.args[0])));
}

/** Calculates the length of a vector.
 * 
 *  Params:
 *      vec = Vector.
 * 
 *  Returns: Number
 */
template<size_t dimensions>
inline lua::Retval vectorLength(lua::Context& context)
{
        context.requireArgs<lua::Table>(1);
        return context.ret(util::vecLength(impl::toVector<dimensions>(context.args[0])));
}

/** Calculates a unit vector out of an existing vector.
 * 
 *  Params:
 *      vec = Vector.
 * 
 *  Returns: Vector
 */
template<size_t dimensions>
inline lua::Retval vectorNormalize(lua::Context& context)
{
        context.requireArgs<lua::Table>(1);
        const auto newVec = util::normalize(impl::toVector<dimensions>(context.args[0]));
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
template<size_t dimensions>
inline lua::Retval vectorSetLength(lua::Context& context)
{
        context.requireArgs<lua::Table, double>(2);
        const auto newVec = util::vecSetLength(impl::toVector<dimensions>(context.args[0]), context.args[1]);
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
                .contains(impl::toVector<2>(context.args[1])));
}

}