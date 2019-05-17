cmake_minimum_required(VERSION 3.1...3.13)


if (${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(
    PAhAom
        VERSION 0.1
        DESCRIPTION "My first rogue-like game."
        LANGUAGES CXX
)


# Lua API++

include_directories("modules/luapp/luapp")
file(GLOB_RECURSE HEADERS "modules/luapp/luapp/luapp.hpp")

set(LUAPP_SOURCES "modules/luapp/luapp/luapp_impl.cpp")
set(LUAPP_HEADERS "modules/luapp/luapp/*.{h,hpp,hxx}")

file(GLOB_RECURSE SOURCES ${LUAPP_SOURCES} ${LUAPP_HEADERS})
add_library(LuaPP STATIC ${SOURCES})

target_include_directories(LuaPP PUBLIC "modules/luapp/luapp")
target_link_libraries(LuaPP PUBLIC lua)

set_target_properties(
    LuaPP
        PROPERTIES
            CXX_STANDARD 17
            CXX_STANDARD_REQUIRED YES
            CXX_EXTENSIONS NO
)


# SCRIPT BINDINGS

set(UTIL_SOURCES "modules/Script/src/Script/*.cpp")
set(UTIL_HEADERS "modules/Script/include/Script/*.hpp")

file(GLOB_RECURSE SOURCES ${UTIL_SOURCES} ${UTIL_HEADERS})
add_library(Script STATIC ${SOURCES})

target_compile_options(Script PUBLIC -Wall -Wextra)
target_include_directories(Script PUBLIC "modules/Script/include")

set_target_properties(
    Script
        PROPERTIES
            LINKER_LANGUAGE CXX
            CXX_STANDARD 17
            CXX_STANDARD_REQUIRED YES
            CXX_EXTENSIONS NO
)


# UTILITIES

set(UTIL_SOURCES "modules/Util/src/Util/*.cpp")
set(UTIL_HEADERS "modules/Util/include/Util/*.hpp")

file(GLOB_RECURSE SOURCES ${UTIL_SOURCES} ${UTIL_HEADERS})
add_library(Util STATIC ${SOURCES})

target_compile_options(Util PUBLIC -Wall -Wextra)
target_include_directories(Util PUBLIC "modules/Util/include")

set_target_properties(
    Util
        PROPERTIES
            LINKER_LANGUAGE CXX
            CXX_STANDARD 17
            CXX_STANDARD_REQUIRED YES
            CXX_EXTENSIONS NO
)


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
            Script
            LuaPP
            Util
)

set_target_properties(
    Pahaom
        PROPERTIES
            CXX_STANDARD 17
            CXX_STANDARD_REQUIRED YES
            CXX_EXTENSIONS NO
)