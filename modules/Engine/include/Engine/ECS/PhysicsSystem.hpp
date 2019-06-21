#pragma once


#include <entt/entity/registry.hpp>


namespace engine::ecs
{

class PhysicsSystem
{
public:

        PhysicsSystem(entt::registry& entities)
        : entities(entities)
        {
        }

        void assignCircleRB()
        {
                
        }

        void assignRectRB()
        {

        }

        void update()
        {

        }

private:

        entt::registry& entities;
};

}