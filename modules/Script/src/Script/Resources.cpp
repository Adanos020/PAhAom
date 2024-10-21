#include <Script/Resources.hpp>

#include <Engine/Resources.hpp>

#include <Script/Lua.hpp>

namespace script
{

namespace impl
{
        template<engine::Resource T>
        inline static sol::table createResourceHandlerTable()
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
}

void loadResources()
{
        lua["fonts"]    = impl::createResourceHandlerTable<sf::Font>();
        lua["textures"] = impl::createResourceHandlerTable<sf::Texture>();

        lua.script_file("data/scripts/resources.lua");
        sol::table resources = lua["resources"];

        static_cast<sol::table>(resources["fonts"]).for_each(impl::loadResource<sf::Font>);
        static_cast<sol::table>(resources["textures"]).for_each(impl::loadResource<sf::Texture>);
}

}
