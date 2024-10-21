#pragma once

#include <SFML/System/Time.hpp>

#include <cstdint>

namespace util
{

static constexpr uint32_t FPS = 60;
static const sf::Time FRAME_TIME = sf::seconds(1.0 / FPS);

}
