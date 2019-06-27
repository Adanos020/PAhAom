#pragma once


#include <Script/Lua.hpp>

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>

#include <string_view>


namespace engine::Settings
{

struct Video
{
        inline static sf::Vector2u resolution = {640, 360};
        inline static sf::Vector2u windowSize = {1280, 720};

        static void load()
        {
                const lua::Table settings = script::luaContext.global["settings"];

                const lua::Table video = settings["video"];
                resolution = {
                        video["resolution"]["x"],
                        video["resolution"]["y"],
                };
                windowSize = {
                        video["window_size"]["x"],
                        video["window_size"]["y"],
                };
        }

        static sf::VideoMode videoMode()
        {
                return {windowSize.x, windowSize.y};
        }

        Video() = delete;
};

}