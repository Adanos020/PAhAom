#pragma once


#include <sol/sol.hpp>

#include <algorithm>


namespace script
{

inline static bool allOf(sol::table tab, sol::function pred)
{
        bool result = true;
        tab.for_each([pred, &result](sol::object, sol::object el)
        {
                if (not pred(el))
                {
                        result = false;
                }
        });
        return result;
}

inline static bool anyOf(sol::table tab, sol::function pred)
{
        bool result = false;
        tab.for_each([pred, &result](sol::object, sol::object el)
        {
                if (pred(el))
                {
                        result = true;
                }
        });
        return result;
}

inline static bool noneOf(sol::table tab, sol::function pred)
{
        bool result = true;
        tab.for_each([pred, &result](sol::object, sol::object el)
        {
                if (pred(el))
                {
                        result = false;
                }
        });
        return result;
}

inline static void loadTable()
{
        lua["allOf"]  = allOf;
        lua["anyOf"]  = anyOf;
        lua["noneOf"] = noneOf;
}

}