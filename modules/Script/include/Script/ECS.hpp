#pragma once


#include <Script/Lua.hpp>

#include <Util/Observer.hpp>


namespace script
{

inline static lua::Retval addEntity(lua::Context& context)
{
        context.requireArgs<lua::Table>(1);
        util::Subject::send(util::Message::AddEntity{context.args[0]});
        return context.ret();
}

inline static lua::Retval setPosition(lua::Context& context)
{
        context.requireArgs<lua::Table, lua::Table>(2);

        lua::Table entity = context.args[0];
        util::Subject::send(util::Message::SetEntityPosition{entity["id"], context.args[1]});
        entity["position"] = context.args[1];

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
        else
        {
                // Scalar
                const float s = context.args[1];
                util::Subject::send(util::Message::SetEntityScale{entity["id"], {s, s}});
                entity["scale"] = lua::Table::records(context, "x", s, "y", s);
        }
        return context.ret();
}

inline static lua::Retval moveBy(lua::Context& context)
{
        context.requireArgs<lua::Table, lua::Table>(2);

        lua::Table entity = context.args[0];
        util::Subject::send(util::Message::MoveEntityBy{entity["id"], context.args[1]});
        entity["position"] = context.args[1];

        return context.ret();
}

inline static lua::Retval rotateBy(lua::Context& context)
{
        context.requireArgs<lua::Table, float>(2);

        lua::Table entity = context.args[0];
        util::Subject::send(util::Message::RotateEntityBy{entity["id"], context.args[1]});
        entity["rotation"] = context.args[1];

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
                entity["scale"] = context.args[1];
        }
        else
        {
                // Scalar
                const float s = context.args[1];
                util::Subject::send(util::Message::ScaleEntityBy{entity["id"], {s, s}});
                entity["scale"] = lua::Table::records(context, "x", s, "y", s);
        }
        return context.ret();
}
        
}