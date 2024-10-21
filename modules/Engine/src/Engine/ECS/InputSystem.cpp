#include <Engine/ECS/InputSystem.hpp>

namespace engine::ecs
{

InputSystem::~InputSystem()
{
        this->clearKeys();
}

void InputSystem::assignInput(sol::table entityTable)
{
        if (entityTable["input"].get_type() == sol::type::table)
        {
                sol::table input = entityTable["input"];
                script::lua.registry()[this->key(this->entityCount++)] = entityTable;
        }
}

void InputSystem::handleInput(const sf::Event& event)
{
        for (uint32_t i = 0; i < this->entityCount; ++i)
        {
                sol::table entityTable = script::lua.registry()[this->key(i)];
                script::callInputHandler(entityTable, entityTable["input"], event);
        }
}

void InputSystem::clearKeys()
{
        for (uint32_t i = 0; i < this->entityCount; ++i)
        {
                script::lua.registry()[this->key(i)] = sol::nil;
        }
        this->entityCount = 0;
}

std::string InputSystem::key(const uint32_t i)
{
        return util::format("%s%u", keyPrefix, i);
}

}