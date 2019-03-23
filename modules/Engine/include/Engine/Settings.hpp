#pragma once


#include <SFML/System/Vector2.hpp>

#include <string_view>


namespace engine::Settings
{

struct Video
{
        inline static const sf::Vector2u resolution = {640, 360};
        inline static       sf::Vector2u windowSize = {1280, 720};

        static void load(std::string_view configPath)
        {

        }

        Video() = delete;
};

}