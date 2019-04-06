#pragma once


#include <lua.hpp>


namespace util
{

inline static lua::State luaState;
inline static lua::Context luaContext = {
        luaState.getRawState(),
        lua::Context::initializeExplicitly
};

}