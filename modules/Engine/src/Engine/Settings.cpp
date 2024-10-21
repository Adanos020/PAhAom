#include <Engine/Settings.hpp>

#include <Script/Lua.hpp>

namespace engine::Settings
{

void Video::load()
{
        const sol::table settings = script::lua["settings"];

        const sol::table video = settings["video"];
        resolution = {
                video["resolution"]["x"],
                video["resolution"]["y"],
        };
        windowSize = {
                video["window_size"]["x"],
                video["window_size"]["y"],
        };
}

sf::VideoMode Video::videoMode()
{
        return {windowSize.x, windowSize.y};
}

sf::Vector2f Video::resolutionSizeRatio()
{
        return {float(resolution.x) / windowSize.x, float(resolution.y) / windowSize.y};
}

}
