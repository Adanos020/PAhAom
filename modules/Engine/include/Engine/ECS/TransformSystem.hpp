#pragma once


#include <Engine/ECS/Components.hpp>

#include <Script/Aux.hpp>

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

        void assignTransform(const entt::entity entity, const util::Vector position,
                             const util::Vector scale, const float rotation)
        {
                this->entities.assign<Transform>(entity, position, scale, rotation);
        }

        void assignTransform(const entt::entity entity, const lua::Table& entityTable)
        {
                const auto position = script::tableFieldOr(entityTable, "position", util::Vector{});
                const auto scale    = script::tableFieldOr(entityTable, "scale", util::Vector{1, 1});
                const auto rotation = entityTable["rotation"].to<float>(0);
                this->assignTransform(entity, position, scale, rotation);
        }

        void setPosition(const entt::entity entity, const util::Vector position)
        {
                this->entities.get<Transform>(entity).position = position;
        }

        void moveBy(const entt::entity entity, const util::Vector displacement)
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

        void setScale(const entt::entity entity, const util::Vector scale)
        {
                this->entities.get<Transform>(entity).scale = scale;
        }

        void scaleBy(const entt::entity entity, const util::Vector scale)
        {
                util::Vector& s = this->entities.get<Transform>(entity).scale;
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