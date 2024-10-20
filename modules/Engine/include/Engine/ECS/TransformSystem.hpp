#pragma once


#include <Engine/ECS/Components.hpp>

#include <Script/Math.hpp>

#include <Util/Observer.hpp>

#include <entt/entity/registry.hpp>


namespace engine::ecs
{

class TransformSystem : public util::Observer
{
public:

        TransformSystem(entt::registry& entities)
        : entities(entities)
        {
                util::Subject::addObserver(this);
        }

        ~TransformSystem()
        {
                util::Subject::deleteObserver(this);
        }

        void assignTransform(const entt::entity entity, const util::FVector position,
                             const util::FVector scale, const float rotation)
        {
                this->entities.emplace<Transform>(entity, position, scale, rotation);
        }

        void assignTransform(const entt::entity entity, sol::table entityTable)
        {
                auto defaultPosition = util::FVector::Zero;
                auto defaultScale = util::FVector{1, 1};
                const auto position = entityTable["position"].get_or(defaultPosition);
                const auto scale    = entityTable["scale"].get_or(defaultScale);
                const auto rotation = entityTable["rotation"].get_or(0.f);
                this->assignTransform(entity, position, scale, rotation);
        }

        void setPosition(const entt::entity entity, const util::FVector position)
        {
                this->entities.get<Transform>(entity).position = position;
        }

        void moveBy(const entt::entity entity, const util::FVector displacement)
        {
                this->entities.get<Transform>(entity).position += displacement;
        }

        void setRotation(const entt::entity entity, const float rotation)
        {
                this->entities.get<Transform>(entity).rotation = rotation;
        }

        void rotateBy(const entt::entity entity, const float rotation)
        {
                this->entities.get<Transform>(entity).rotation += rotation;
        }

        void setScale(const entt::entity entity, const util::FVector scale)
        {
                this->entities.get<Transform>(entity).scale = scale;
        }

        void scaleBy(const entt::entity entity, const util::FVector scale)
        {
                util::FVector& s = this->entities.get<Transform>(entity).scale;
                s.x *= scale.x;
                s.y *= scale.y;
        }

private:

        virtual void receive(const util::Message& message) override
        {
                std::visit(util::MsgHandlers {
                        [this](const util::Message::SetEntityPosition& msg)
                        {
                                this->setPosition(msg.entity, msg.position);
                        },
                        [this](const util::Message::MoveEntityBy& msg)
                        {
                                this->moveBy(msg.entity, msg.displacement);
                        },
                        [this](const util::Message::SetEntityRotation& msg)
                        {
                                this->setRotation(msg.entity, msg.rotation);
                        },
                        [this](const util::Message::RotateEntityBy& msg)
                        {
                                this->rotateBy(msg.entity, msg.rotation);
                        },
                        [this](const util::Message::SetEntityScale& msg)
                        {
                                this->setScale(msg.entity, msg.scale);
                        },
                        [this](const util::Message::ScaleEntityBy& msg)
                        {
                                this->scaleBy(msg.entity, msg.scale);
                        },
                        util::discardTheRest
                }, message.msg);
        }

private:

        entt::registry& entities;
};

}