#pragma once


// #include <lua.hpp>
#include <luapp.hpp>


namespace script
{

inline static lua::State luaState;
inline static lua::Context luaContext = {
        luaState.getRawState(),
        lua::Context::initializeExplicitly
};

}