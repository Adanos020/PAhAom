cmake_minimum_required(VERSION 3.1...3.13)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(
    PAhAom
        VERSION 0.1
        DESCRIPTION "My first rogue-like game."
        LANGUAGES CXX
)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Lua API++
include_directories("modules/luapp/luapp")
file(GLOB HEADERS "modules/luapp/luapp/luapp.hpp")

set(LUAPP_SOURCES "modules/luapp/luapp/luapp_impl.cpp")
set(LUAPP_HEADERS "modules/luapp/luapp/*.{h,hpp,hxx}")

file(GLOB_RECURSE SOURCES ${LUAPP_SOURCES} ${LUAPP_HEADERS})
add_library(LuaPP STATIC ${SOURCES} ${HEADERS})

target_include_directories(LuaPP PUBLIC "modules/luapp/luapp")
target_link_libraries(LuaPP PUBLIC lua)

# EnTT
include_directories("modules/entt/src")

# SCRIPT BINDINGS
include_directories("modules/Script/include")

# UTILITIES
include_directories("modules/Util/include")

# MAIN EXEC
set(PAHAOM_SOURCES "modules/Engine/src/Engine/*.cpp")
set(PAHAOM_HEADERS "modules/Engine/include/Engine/*.hpp")

file(GLOB_RECURSE SOURCES ${PAHAOM_SOURCES} ${PAHAOM_HEADERS})
add_executable(Pahaom ${SOURCES})

target_compile_options(Pahaom PUBLIC -Wall -Wextra)
target_include_directories(Pahaom PUBLIC "modules/Engine/include")
target_link_libraries(
    Pahaom
        PUBLIC
            sfml-graphics-d
            sfml-window-d
            sfml-audio-d
            sfml-system-d
            LuaPP
)