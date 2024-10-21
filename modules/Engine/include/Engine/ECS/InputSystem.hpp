#pragma once

#include <Script/Input.hpp>

#include <SFML/Window/Event.hpp>

#include <Util/String.hpp>

namespace engine::ecs
{

class InputSystem
{
public:
        InputSystem() = default;

        ~InputSystem();

        void assignInput(sol::table entityTable);
        void handleInput(const sf::Event& event);
        void clearKeys();

private:
        std::string key(const uint32_t i);

private:
        uint32_t entityCount = 0;
        inline static util::CStr keyPrefix = "pahaom_entity_input_";
};

}