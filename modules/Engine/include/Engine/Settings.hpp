#pragma once


#include <Util/Lua.hpp>

#include <SFML/System/Vector2.hpp>

#include <string_view>


namespace engine::Settings
{

struct Video
{
        inline static sf::Vector2u resolution = {640, 360};
        inline static sf::Vector2u windowSize = {1280, 720};

        static void load()
        {
                const lua::Table settings = util::luaContext.global["Settings"];

                const lua::Table video = settings["Video"];
                resolution = {
                        video["resolution"]["x"],
                        video["resolution"]["y"],
                };
        }

        Video() = delete;
};

}