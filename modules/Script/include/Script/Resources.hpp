#pragma once


#include <Engine/Resources.hpp>

#include <Script/Lua.hpp>


namespace script
{

template<engine::Resource T>
inline static sol::table addResourceHandlerTable()
{
        return lua.create_table_with(
                "load",      &engine::Resources<T>::load,
                "unload",    &engine::Resources<T>::unload,
                "unloadAll", &engine::Resources<T>::unloadAll);
}

template<engine::Resource T>
inline static void loadResource(sol::object, sol::object res)
{
        const auto resource = res.as<sol::table>();
        const std::string id   = resource[1];
        const std::string path = resource[2];

        if constexpr (std::is_same_v<T, sf::Font>)
        {
                engine::Resources<T>::load(id, "data/fonts/" + path);
        }
        else if constexpr (std::is_same_v<T, sf::Texture>)
        {
                engine::Resources<T>::load(id, "data/textures/" + path);
        }
}

inline static void loadResources()
{
        lua["fonts"]    = addResourceHandlerTable<sf::Font>();
        lua["textures"] = addResourceHandlerTable<sf::Texture>();

        lua.script_file("data/scripts/resources.lua");
        sol::table resources = lua["resources"];

        static_cast<sol::table>(resources["fonts"]).for_each(loadResource<sf::Font>);
        static_cast<sol::table>(resources["textures"]).for_each(loadResource<sf::Texture>);
}

}