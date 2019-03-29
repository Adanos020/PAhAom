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


# SELENE

include_directories("modules/Selene/include")
file(GLOB_RECURSE HEADERS "modules/Selene/include/*.h")


# UTILITIES

set(UTIL_SOURCES "modules/Util/src/Util/*.cpp")
set(UTIL_HEADERS "modules/Util/include/Util/*.hpp")

file(GLOB_RECURSE SOURCES ${UTIL_SOURCES} ${UTIL_HEADERS})
add_library(Util STATIC ${SOURCES})

target_include_directories(Util PUBLIC "modules/Util/include")

set_target_properties(
    Util
        PROPERTIES
            LINKER_LANGUAGE CXX
            CXX_STANDARD 17
            CXX_STANDARD_REQUIRED YES
            CXX_EXTENSIONS NO
            INTERPROCEDURAL_OPTIMIZATION true
)


# MAIN EXEC

set(PAHAOM_SOURCES "modules/Engine/src/Engine/*.cpp")
set(PAHAOM_HEADERS "modules/Engine/include/Engine/*.hpp")

file(GLOB_RECURSE SOURCES ${PAHAOM_SOURCES} ${PAHAOM_HEADERS})
add_executable(pahaom ${SOURCES})

target_include_directories(pahaom PUBLIC "modules/Engine/include")
target_link_libraries(
    pahaom
        PUBLIC
            sfml-graphics-d
            sfml-window-d
            sfml-audio-d
            sfml-system-d
            lua
            Util
)

set_target_properties(
    pahaom
        PROPERTIES
            CXX_STANDARD 17
            CXX_STANDARD_REQUIRED YES
            CXX_EXTENSIONS NO
            INTERPROCEDURAL_OPTIMIZATION true
)