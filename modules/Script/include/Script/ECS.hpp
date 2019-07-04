#pragma once


#include <Script/Lua.hpp>
#include <Script/Math.hpp>

#include <Util/Observer.hpp>

#include <iostream>


namespace script
{

// Transform

inline static void setPosition(sol::table entity, sf::Vector2f position)
{
        util::Subject::send(util::Message::SetEntityPosition{entity["id"], position});
        entity.set("position", position);
}

inline static void moveBy(sol::table entity, sf::Vector2f displacement)
{
        util::Subject::send(util::Message::MoveEntityBy{entity["id"], displacement});
        const auto pos = entity.get_or("position", sol::make_user(sf::Vector2f{0, 0}));
        entity.set("position", pos + displacement);
}

inline static void setRotation(sol::table entity, const float rotation)
{
        util::Subject::send(util::Message::SetEntityRotation{entity["id"], rotation});
        entity.set("rotation", rotation);
}

inline static void rotateBy(sol::table entity, const float rotation)
{
        util::Subject::send(util::Message::RotateEntityBy{entity["id"], rotation});
        entity.set("rotation", entity.get_or("rotation", 0.f) + rotation);
}

inline static void setScale(sol::table entity, const sf::Vector2f scale)
{
        util::Subject::send(util::Message::SetEntityScale{entity["id"], scale});
        entity.set("scale", scale);
}

inline static void setScale(sol::table entity, const float scale)
{
        setScale(entity, {scale, scale});
}

inline static void scaleBy(sol::table entity, const sf::Vector2f scale)
{
        util::Subject::send(util::Message::ScaleEntityBy{entity["id"], scale});
        const auto current = entity.get_or("scale", sol::make_user(sf::Vector2f{1, 1}));
        entity.set("scale", sf::Vector2f{current.x * scale.x, current.y * scale.y});
}

inline static void scaleBy(sol::table entity, const float scale)
{
        scaleBy(entity, {scale, scale});
}

// Physics

inline static void setVelocity(sol::table entity, const sf::Vector2f velocity)
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

inline static void accelerateBy(sol::table entity, const sf::Vector2f acceleration)
{
        if (entity["rigidBody"].get_type() == sol::type::table)
        {
                util::Subject::send(util::Message::AccelerateEntityBy{entity["id"], acceleration});
                sol::table rigidBody = entity["rigidBody"];
                const auto pos = rigidBody.get_or("velocity", sol::make_user(sf::Vector2f{0, 0}));
                rigidBody.set("velocity", pos + acceleration);
        }
        else
        {
                std::cerr << "Attempting to assign velocity to an entity with no rigid body." << std::endl;
        }
}

inline static void setMass(sol::table entity, const float mass)
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

inline static void addEntity(sol::table entity)
{
        util::Subject::send(util::Message::AddEntity{entity});
}

inline static void loadECS()
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