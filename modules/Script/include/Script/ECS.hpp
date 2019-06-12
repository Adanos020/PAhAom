#pragma once


#include <Script/Lua.hpp>

#include <Util/Observer.hpp>


namespace script
{

inline static lua::Retval setPosition(lua::Context& context)
{
        context.requireArgs<lua::Table, lua::Table>(2);
        util::Subject::send({util::Message::SetPosition{context.args[0]["id"], context.args[1]}});
        return context.ret();
}

inline static lua::Retval setRotation(lua::Context& context)
{
        context.requireArgs<lua::Table, float>(2);
        util::Subject::send({util::Message::SetRotation{context.args[0]["id"], context.args[1]}});
        return context.ret();
}

inline static lua::Retval setScale(lua::Context& context)
{
        context.requireArgs<lua::Table, lua::Table>(2);
        util::Subject::send({util::Message::SetScale{context.args[0]["id"], context.args[1]}});
        return context.ret();
}
        
}