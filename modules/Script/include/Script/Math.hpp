#pragma once


#include <Script/Lua.hpp>

#include <SFML/Graphics/Rect.hpp>

#include <algorithm>


namespace script
{

namespace impl
{
        inline double lerpNumber(double val1, double val2, double alpha)
        {
                return (1.0 - alpha) * val1 + alpha * val2;
        }

        inline double normalizeNumber(double val, double lo, double hi)
        {
                return (val - lo) / (hi - lo);
        }

        inline double mapNumber(double val, double lo1, double hi1, double lo2, double hi2)
        {
                return normalizeNumber(val, lo1, hi1) * (hi2 - lo2) + lo2;
        }

        inline bool isVector(const lua::Table& vec)
        {
                return vec["x"].is<double>() and vec["y"].is<double>();
        }

        inline sf::Vector2f toVector(const lua::Table& vec)
        {
                return {vec["x"], vec["y"]};
        }

        inline bool vectorsEqual(const lua::Table& vec1, const lua::Table& vec2)
        {
                return vec1["x"] == vec2["x"] and vec1["y"] == vec2["y"];
        }

        inline bool isRectangle(const lua::Table& rect)
        {
                return isVector(rect["position"]) and isVector(rect["size"]);
        }

        inline sf::FloatRect toRectangle(const lua::Table& rect)
        {
                return {toVector(rect["position"]), toVector(rect["size"])};
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
        return context.ret(impl::lerpNumber(context.args[0], context.args[1], context.args[2]));
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
        return context.ret(impl::normalizeNumber(context.args[0], context.args[1], context.args[2]));
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
        return context.ret(impl::mapNumber(context.args[0], context.args[1], context.args[2],
                                           context.args[3], context.args[4]));
}

/** Checks if given table is a vector, i.e. it has two numbers called "x" and "y".
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

        const lua::Table vec1 = context.args[0];
        const lua::Table vec2 = context.args[1];

        if (impl::isVector(vec1) and impl::isVector(vec2))
        {
                return context.ret(impl::vectorsEqual(vec1, vec2));
        }

        return context.ret(false);
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

        const lua::Table t1 = context.args[0];
        const lua::Table t2 = context.args[1];

        if (impl::isRectangle(t1) and impl::isRectangle(t2))
        {
                const sf::FloatRect rect1 = impl::toRectangle(t1);
                const sf::FloatRect rect2 = impl::toRectangle(t2);
                return context.ret(rect1.intersects(rect2));
        }
        
        return context.ret();
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

        const lua::Table t1 = context.args[0];
        const lua::Table t2 = context.args[1];

        if (impl::isRectangle(t1) and impl::isVector(t2))
        {
                const sf::FloatRect rect = impl::toRectangle(t1);
                const sf::Vector2f vec = impl::toVector(t2);
                return context.ret(rect.contains(vec));
        }

        return context.ret();
}

}