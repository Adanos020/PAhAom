#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>

namespace engine::Settings
{

struct Video
{
public:
        inline static sf::Vector2u resolution = {640, 360};
        inline static sf::Vector2u windowSize = {1280, 720};

        static void load();
        static sf::VideoMode videoMode();
        static sf::Vector2f resolutionSizeRatio();

private:
        Video() = delete;
};

}
