#pragma once


#include <Script/Input.hpp>

#include <vector>


namespace engine::ecs
{

class InputSystem
{
public:

        InputSystem()
        : entityCount(0)
        {
        }

        ~InputSystem()
        {
                this->clearKeys();
        }

        void assignInput(sol::table entityTable)
        {
                if (entityTable["input"].get_type() == sol::type::table)
                {
                        sol::table input = entityTable["input"];
                        script::lua.registry()[this->key(this->entityCount++)] = entityTable;
                }
        }

        void handleInput(const sf::Event& event)
        {
                for (std::uint32_t i = 0; i < this->entityCount; ++i)
                {
                        sol::table entityTable = script::lua.registry()[this->key(i)];
                        script::callInputHandler(entityTable, entityTable["input"], event);
                }
        }

        void clearKeys()
        {
                for (std::uint32_t i = 0; i < this->entityCount; ++i)
                {
                        script::lua.registry()[this->key(i)] = sol::nil;
                }
                this->entityCount = 0;
        }

private:

        std::string key(const std::uint32_t i)
        {
                return util::format("%s%u", keyPrefix, i);
        }

private:

        std::uint32_t entityCount;
        inline static util::CStr keyPrefix = "pahaom_entity_input_";
};

}