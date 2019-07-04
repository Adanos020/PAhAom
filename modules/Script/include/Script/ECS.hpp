#pragma once


#include <Script/Lua.hpp>
#include <Script/Math.hpp>

#include <Util/Observer.hpp>

#include <iostream>


namespace script
{

// Transform

inline static void setPosition(sol::table entity, sol::table position)
{
        util::Subject::send(util::Message::SetEntityPosition{entity["id"], position});
        entity.set("position", position);
}

inline static void moveBy(sol::table entity, sol::table displacement)
{
        const util::Vector dpos = displacement;
        util::Subject::send(util::Message::MoveEntityBy{entity["id"], dpos});
        entity.set("position", lua.create_table_with(
                "x", entity.traverse_get<float>("position", "x") + dpos.x,
                "y", entity.traverse_get<float>("position", "y") + dpos.y));
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

inline static void setScale(sol::table entity, sol::object scale)
{
        if (scale.get_type() == sol::type::table)
        {
                // Vector
                util::Subject::send(util::Message::SetEntityScale{entity["id"], scale.as<sol::table>()});
                entity.set("scale", scale);
        }
        else if (scale.get_type() == sol::type::number)
        {
                // Scalar
                const float s = scale.as<float>();
                util::Subject::send(util::Message::SetEntityScale{entity["id"], {s, s}});
                entity.set("scale", vector(s, s));
        }
}

inline static void scaleBy(sol::table entity, sol::object scale)
{
        if (scale.get_type() == sol::type::table)
        {
                // Vector
                const util::Vector s = scale.as<sol::table>();
                util::Subject::send(util::Message::ScaleEntityBy{entity["id"], s});
                entity.set("scale", lua.create_table_with(
                        "x", entity.traverse_get<float>("scale", "x") * s.x,
                        "y", entity.traverse_get<float>("scale", "y") * s.y));
        }
        else if (scale.get_type() == sol::type::number)
        {
                // Scalar
                const auto s = scale.as<float>();
                util::Subject::send(util::Message::ScaleEntityBy{entity["id"], {s, s}});
                entity.set("scale", lua.create_table_with(
                        "x", entity.traverse_get<float>("scale", "x") * s,
                        "y", entity.traverse_get<float>("scale", "y") * s));
        }
}

// Physics

inline static void setVelocity(sol::table entity, const sol::table velocity)
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

inline static void accelerateBy(sol::table entity, const sol::table acceleration)
{
        if (entity["rigidBody"].get_type() == sol::type::table)
        {
                const util::Vector acc = acceleration;
                util::Subject::send(util::Message::AccelerateEntityBy{entity["id"], acc});
                entity.traverse_set("rigidBody", "velocity", lua.create_table_with(
                        "x", entity.traverse_get<float>("rigidBody", "velocity", "x") + acc.x,
                        "y", entity.traverse_get<float>("rigidBody", "velocity", "y") + acc.y));
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
                "setRotation",  setRotation,
                "setScale",     setScale,
                "moveBy",       moveBy,
                "rotateBy",     rotateBy,
                "scaleBy",      scaleBy,
                "setVelocity",  setVelocity,
                "accelerateBy", accelerateBy,
                "setMass",      setMass);
}

}