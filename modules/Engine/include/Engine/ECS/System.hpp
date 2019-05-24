#pragma once


#include <Util/Constants.hpp>

#include <entt/entity/registry.hpp>


namespace engine::ecs
{

class System
{
public:

        virtual void update() = 0;

private:

        entt::registry registry;
};

}