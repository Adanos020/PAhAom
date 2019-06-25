#pragma once


#include <Script/Input.hpp>

#include <vector>


namespace engine::ecs
{

class InputSystem
{
public:

        ~InputSystem()
        {
                this->clearKeys();
        }

        void assignInput(lua::Valref entityTable)
        {
                if (entityTable["input"].is<lua::Table>())
                {
                        lua::Table input = entityTable["input"];
                        script::assignEmptyInputHandlers(input);
                        const lua::RegistryKey key = script::luaContext.registry.store(entityTable);
                        this->entityKeys.push_back(key);
                }
        }

        void handleInput(const sf::Event& event, lua::Valset& args)
        {
                for (const lua::RegistryKey key : this->entityKeys)
                {
                        lua::Table entity = script::luaContext.registry[key];
                        args[0] = entity;
                        entity["input"][script::EVENT_HANDLERS[event.type]](args);
                }
        }

        void clearKeys()
        {
                for (const lua::RegistryKey key : this->entityKeys)
                {
                        script::luaContext.registry[key] = lua::nil;
                }
                this->entityKeys.clear();
        }

private:

        std::vector<lua::RegistryKey> entityKeys;
};

}