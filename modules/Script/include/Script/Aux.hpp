#pragma once


#include <Script/Lua.hpp>


namespace script
{

/** Chooses the value of the `field` of given `table` if it exists, `rFalse` otherwise. Use only for
 *  value types that Valref is not implicitly convertible to, in other cases use its overload of
 *  `to` with a backup value.
 */
template<typename Return>
inline static Return tableFieldOr(const lua::Table& table, const std::string& field, const Return rFalse)
{
        if (lua::Value v = std::move(table[field]))
        {
                if constexpr (std::is_fundamental_v<Return>)
                {
                        return v.to<Return>();
                }
                else
                {
                        return Return{lua::Table{v}};
                }
        }
        return rFalse;
}

}