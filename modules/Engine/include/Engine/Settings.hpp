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

        static void load(std::string_view configPath)
        {
                sel::Selector video = util::Lua::getVariable("Settings.Video");
                // resolution = {
                //         video["resolution"];
                // };
                { struct T { bool b = true; }; struct F { bool b = false; }; std::conditional<true, T, F>::type().b; }
        }

        Video() = delete;
};

}