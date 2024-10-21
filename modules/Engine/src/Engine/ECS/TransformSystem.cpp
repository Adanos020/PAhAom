#include <Engine/ECS/TransformSystem.hpp>

#include <Engine/ECS/Components.hpp>

namespace engine::ecs
{

TransformSystem::TransformSystem(entt::registry& entities)
        : entities(entities)
{
        util::Subject::addObserver(this);
}

TransformSystem::~TransformSystem()
{
        util::Subject::deleteObserver(this);
}

void TransformSystem::assignTransform(
        const entt::entity entity,
        const util::FVector position,
        const util::FVector scale,
        const float rotation
) {
        this->entities.emplace<Transform>(entity, position, scale, rotation);
}

void TransformSystem::assignTransform(const entt::entity entity, sol::table entityTable)
{
        auto defaultPosition = util::FVector::Zero;
        auto defaultScale = util::FVector{1, 1};
        const auto position = entityTable["position"].get_or(defaultPosition);
        const auto scale    = entityTable["scale"].get_or(defaultScale);
        const auto rotation = entityTable["rotation"].get_or(0.f);
        this->assignTransform(entity, position, scale, rotation);
}

void TransformSystem::setPosition(const entt::entity entity, const util::FVector position)
{
        this->entities.get<Transform>(entity).position = position;
}

void TransformSystem::moveBy(const entt::entity entity, const util::FVector displacement)
{
        this->entities.get<Transform>(entity).position += displacement;
}

void TransformSystem::setRotation(const entt::entity entity, const float rotation)
{
        this->entities.get<Transform>(entity).rotation = rotation;
}

void TransformSystem::rotateBy(const entt::entity entity, const float rotation)
{
        this->entities.get<Transform>(entity).rotation += rotation;
}

void TransformSystem::setScale(const entt::entity entity, const util::FVector scale)
{
        this->entities.get<Transform>(entity).scale = scale;
}

void TransformSystem::scaleBy(const entt::entity entity, const util::FVector scale)
{
        util::FVector& s = this->entities.get<Transform>(entity).scale;
        s.x *= scale.x;
        s.y *= scale.y;
}

void TransformSystem::receive(const util::Message& message)
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

}