#include <Script/ECS.hpp>

#include <Util/Observer.hpp>

#include <iostream>

namespace script
{

// Transform

void setPosition(sol::table entity, sf::Vector2f position)
{
        util::Subject::send(util::Message::SetEntityPosition{entity["id"], position});
        entity.set("position", position);
}

void moveBy(sol::table entity, sf::Vector2f displacement)
{
        util::Subject::send(util::Message::MoveEntityBy{entity["id"], displacement});
        auto defaultPosition = sf::Vector2f{0, 0};
        const auto pos = entity["position"].get_or(defaultPosition);
        entity.set("position", pos + displacement);
}

void setRotation(sol::table entity, const float rotation)
{
        util::Subject::send(util::Message::SetEntityRotation{entity["id"], rotation});
        entity.set("rotation", rotation);
}

void rotateBy(sol::table entity, const float rotation)
{
        util::Subject::send(util::Message::RotateEntityBy{entity["id"], rotation});
        entity.set("rotation", entity["rotation"].get_or(0.f) + rotation);
}

void setScale(sol::table entity, const sf::Vector2f scale)
{
        util::Subject::send(util::Message::SetEntityScale{entity["id"], scale});
        entity.set("scale", scale);
}

void setScale(sol::table entity, const float scale)
{
        setScale(entity, {scale, scale});
}

void scaleBy(sol::table entity, const sf::Vector2f scale)
{
        util::Subject::send(util::Message::ScaleEntityBy{entity["id"], scale});
        auto defaultScale = sf::Vector2f{1, 1};
        const auto current = entity["scale"].get_or(defaultScale);
        entity.set("scale", sf::Vector2f{current.x * scale.x, current.y * scale.y});
}

void scaleBy(sol::table entity, const float scale)
{
        scaleBy(entity, {scale, scale});
}

// Physics

void setVelocity(sol::table entity, const sf::Vector2f velocity)
{
        if (entity["rigidBody"].get_type() == sol::type::table)
        {
                util::Subject::send(util::Message::SetEntityVelocity{entity["id"], velocity});
                entity.traverse_set("rigidBody", "velocity", velocity);
        }
        else
        {
                std::cerr << "Attempting to assign velocity to an entity with no rigid body." << std::endl;
        }
}

void accelerateBy(sol::table entity, const sf::Vector2f acceleration)
{
        if (entity["rigidBody"].get_type() == sol::type::table)
        {
                util::Subject::send(util::Message::AccelerateEntityBy{entity["id"], acceleration});
                sol::table rigidBody = entity["rigidBody"];
                auto defaultVelocity = sf::Vector2f{0, 0};
                const auto pos = rigidBody["velocity"].get_or(defaultVelocity);
                rigidBody.set("velocity", pos + acceleration);
        }
        else
        {
                std::cerr << "Attempting to assign velocity to an entity with no rigid body." << std::endl;
        }
}

void setMass(sol::table entity, const float mass)
{
        if (entity["rigidBody"].get_type() == sol::type::table)
        {
                util::Subject::send(util::Message::SetEntityMass{entity["id"], mass});
                entity.traverse_set("rigidBody", "mass", mass);
        }
        else
        {
                std::cerr << "Attempting to assign mass to an entity with no rigid body." << std::endl;
        }
}

// General

void addEntity(sol::table entity)
{
        util::Subject::send(util::Message::AddEntity{entity});
}

void loadECS()
{
        lua.create_named_table("entity",
                "add",          addEntity,
                "setPosition",  setPosition,
                "moveBy",       moveBy,
                "setRotation",  setRotation,
                "rotateBy",     rotateBy,
                "setScale",     sol::overload(
                        static_cast<void(*)(sol::table, sf::Vector2f)>(setScale),
                        static_cast<void(*)(sol::table, float)>(setScale)),
                "scaleBy",      sol::overload(
                        static_cast<void(*)(sol::table, sf::Vector2f)>(scaleBy),
                        static_cast<void(*)(sol::table, float)>(scaleBy)),
                "setVelocity",  setVelocity,
                "accelerateBy", accelerateBy,
                "setMass",      setMass);
}

}
