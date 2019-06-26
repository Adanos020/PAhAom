#pragma once


#include <Script/Lua.hpp>

#include <Util/Observer.hpp>


namespace script
{

// General

inline static lua::Retval addEntity(lua::Context& context)
{
        context.requireArgs<lua::Table>(1);
        util::Subject::send(util::Message::AddEntity{context.args[0]});
        return context.ret();
}

// Transform

inline static lua::Retval setPosition(lua::Context& context)
{
        context.requireArgs<lua::Table, lua::Table>(2);

        lua::Table entity = context.args[0];
        util::Subject::send(util::Message::SetEntityPosition{entity["id"], context.args[1]});
        entity["position"] = context.args[1];

        return context.ret();
}

inline static lua::Retval moveBy(lua::Context& context)
{
        context.requireArgs<lua::Table, lua::Table>(2);

        lua::Table entity = context.args[0];
        util::Subject::send(util::Message::MoveEntityBy{entity["id"], context.args[1]});
        entity["position"]["x"] = entity["position"]["x"] + context.args[1]["x"];
        entity["position"]["y"] = entity["position"]["y"] + context.args[1]["y"];

        return context.ret();
}

inline static lua::Retval setRotation(lua::Context& context)
{
        context.requireArgs<lua::Table, float>(2);

        lua::Table entity = context.args[0];
        util::Subject::send(util::Message::SetEntityRotation{entity["id"], context.args[1]});
        entity["rotation"] = context.args[1];

        return context.ret();
}

inline static lua::Retval rotateBy(lua::Context& context)
{
        context.requireArgs<lua::Table, float>(2);

        lua::Table entity = context.args[0];
        util::Subject::send(util::Message::RotateEntityBy{entity["id"], context.args[1]});
        entity["rotation"] = entity["rotation"] + context.args[1];

        return context.ret();
}

inline static lua::Retval setScale(lua::Context& context)
{
        context.requireArgs<lua::Table>(2);

        lua::Table entity = context.args[0];
        if (context.args[1].is<lua::Table>())
        {
                // Vector
                util::Subject::send(util::Message::SetEntityScale{entity["id"], context.args[1]});
                entity["scale"] = context.args[1];
        }
        else if (context.args[1].is<float>())
        {
                // Scalar
                const float s = context.args[1];
                util::Subject::send(util::Message::SetEntityScale{entity["id"], {s, s}});
                entity["scale"] = lua::Table::records(context, "x", s, "y", s);
        }
        return context.ret();
}

inline static lua::Retval scaleBy(lua::Context& context)
{
        context.requireArgs<lua::Table>(2);

        lua::Table entity = context.args[0];
        if (context.args[1].is<lua::Table>())
        {
                // Vector
                util::Subject::send(util::Message::ScaleEntityBy{entity["id"], context.args[1]});
                entity["scale"]["x"] = entity["scale"]["x"] * context.args[1]["x"];
                entity["scale"]["y"] = entity["scale"]["y"] * context.args[1]["y"];
        }
        else if (context.args[1].is<float>())
        {
                // Scalar
                const float s = context.args[1];
                util::Subject::send(util::Message::ScaleEntityBy{entity["id"], {s, s}});
                entity["scale"]["x"] = entity["scale"]["x"] * s;
                entity["scale"]["y"] = entity["scale"]["y"] * s;
        }
        return context.ret();
}

// Physics

inline static lua::Retval setVelocity(lua::Context& context)
{
        context.requireArgs<lua::Table, lua::Table>(2);

        lua::Table entity = context.args[0];
        
        if (entity["rigidBody"].is<lua::Table>())
        {
                util::Subject::send(util::Message::SetEntityVelocity{entity["id"], context.args[1]});

                lua::Table rigidBody = entity["rigidBody"];
                rigidBody["velocity"]["x"] = context.args[1]["x"];
                rigidBody["velocity"]["y"] = context.args[1]["y"];
        }
        else
        {
                context.error("Attempting to assign velocity to an entity with no rigid body.");
        }
        return context.ret();
}

inline static lua::Retval accelerateBy(lua::Context& context)
{
        context.requireArgs<lua::Table, lua::Table>(2);

        lua::Table entity = context.args[0];

        if (entity["rigidBody"].is<lua::Table>())
        {
                util::Subject::send(util::Message::AccelerateEntityBy{entity["id"], context.args[1]});

                lua::Table rigidBody = entity["rigidBody"];
                rigidBody["velocity"]["x"] = rigidBody["velocity"]["x"] + context.args[1]["x"];
                rigidBody["velocity"]["y"] = rigidBody["velocity"]["y"] + context.args[1]["y"];
        }
        else
        {
                context.error("Attempting to assign velocity to an entity with no rigid body.");
        }
        return context.ret();
}

inline static lua::Retval setMass(lua::Context& context)
{
        context.requireArgs<lua::Table, float>(2);

        lua::Table entity = context.args[0];
        
        if (entity["rigidBody"].is<lua::Table>())
        {
                util::Subject::send(util::Message::SetEntityVelocity{entity["id"], context.args[1]});
                entity["rigidBody"]["mass"] = context.args[1];
        }
        else
        {
                context.error("Attempting to assign mass to an entity with no rigid body.");
        }
        return context.ret();
}

inline static lua::Retval addMass(lua::Context& context)
{
        context.requireArgs<lua::Table, float>(2);

        lua::Table entity = context.args[0];

        if (entity["rigidBody"].is<lua::Table>())
        {
                util::Subject::send(util::Message::AccelerateEntityBy{entity["id"], context.args[1]});
                entity["rigidBody"]["mass"] = entity["rigidBody"]["mass"] + context.args[1];
        }
        else
        {
                context.error("Attempting to assign mass to an entity with no rigid body.");
        }
        return context.ret();
}

}