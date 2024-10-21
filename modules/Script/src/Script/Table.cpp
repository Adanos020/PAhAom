#include <Script/Table.hpp>

#include <Script/Lua.hpp>

#include <sol/sol.hpp>

namespace script
{

bool allOf(sol::table tab, sol::function pred)
{
        bool result = true;
        tab.for_each([pred, &result](sol::object, sol::object el)
        {
                if (!pred(el))
                {
                        result = false;
                }
        });
        return result;
}

bool anyOf(sol::table tab, sol::function pred)
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

bool noneOf(sol::table tab, sol::function pred)
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

void loadTable()
{
        lua["allOf"]  = allOf;
        lua["anyOf"]  = anyOf;
        lua["noneOf"] = noneOf;
}

}
