#pragma once

#include <Engine/ECS/InputSystem.hpp>
#include <Engine/ECS/PhysicsSystem.hpp>
#include <Engine/ECS/RenderSystem.hpp>
#include <Engine/ECS/TransformSystem.hpp>

#include <Script/Lua.hpp>

#include <Util/Observer.hpp>

#include <entt/entity/registry.hpp>

namespace engine::ecs
{

class Systems : public util::Observer
{
public:
        Systems();
        ~Systems();

        void addEntity(sol::table entityTable);
        void reset();

public:
        InputSystem input;
        PhysicsSystem physics;
        RenderSystem render;
        TransformSystem transform;

private:
        virtual void receive(const util::Message& message) override;

private:
        entt::registry entities;
};

}
