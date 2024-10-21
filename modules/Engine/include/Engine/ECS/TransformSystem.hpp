#pragma once

#include <Script/Math.hpp>

#include <Util/Observer.hpp>

#include <entt/entity/registry.hpp>

namespace engine::ecs
{

class TransformSystem : public util::Observer
{
public:
        TransformSystem(entt::registry& entities);
        ~TransformSystem();

        void assignTransform(const entt::entity entity, const util::FVector position,
                             const util::FVector scale, const float rotation);
        void assignTransform(const entt::entity entity, sol::table entityTable);
        void setPosition(const entt::entity entity, const util::FVector position);
        void moveBy(const entt::entity entity, const util::FVector displacement);
        void setRotation(const entt::entity entity, const float rotation);
        void rotateBy(const entt::entity entity, const float rotation);
        void setScale(const entt::entity entity, const util::FVector scale);
        void scaleBy(const entt::entity entity, const util::FVector scale);

private:
        virtual void receive(const util::Message& message) override;

private:
        entt::registry& entities;
};

}
