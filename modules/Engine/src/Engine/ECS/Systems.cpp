#include <Engine/ECS/Systems.hpp>

namespace engine::ecs
{

Systems::Systems()
        : physics(entities)
        , render(entities)
        , transform(entities)
{
        util::Subject::addObserver(this);
}

Systems::~Systems()
{
        util::Subject::deleteObserver(this);
}

void Systems::addEntity(sol::table entityTable)
{
        const entt::entity entity = this->entities.create();
        entityTable["id"] = entity;

        this->input.assignInput(entityTable);
        this->physics.assignPhysics(entity, entityTable);
        this->transform.assignTransform(entity, entityTable);
        this->render.assignGraphics(entity, entityTable);
}

void Systems::reset()
{
        this->input.clearKeys();
        this->entities.clear();
}

void Systems::receive(const util::Message& message)
{
        std::visit(util::MsgHandlers {
                [this](const util::Message::AddEntity& msg)
                {
                        this->addEntity(msg.data);
                },
                util::discardTheRest
        }, message.msg);
}

}
