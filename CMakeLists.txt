cmake_minimum_required(VERSION 3.1...3.13)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(
    PAhAom
        VERSION 0.1
        DESCRIPTION "2D game engine."
        LANGUAGES CXX
)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Sol3
include_directories("modules/sol2/include")

# EnTT
include_directories("modules/entt/src")

# SCRIPT BINDINGS
include_directories("modules/Script/include")

# UTILITIES
include_directories("modules/Util/include")

# MAIN EXEC
set(PAHAOM_SOURCES "modules/Engine/src/Engine/Engine.cpp")
set(PAHAOM_HEADERS "modules/Engine/include/Engine/*.hpp")

file(GLOB_RECURSE SOURCES ${PAHAOM_SOURCES} ${PAHAOM_HEADERS})
add_executable(Pahaom ${SOURCES})

target_compile_options(Pahaom PUBLIC -Wall -Wextra)
target_include_directories(Pahaom PUBLIC "modules/Engine/include")
target_link_libraries(
    Pahaom
        PUBLIC
            sfml-graphics
            sfml-window
            sfml-audio
            sfml-system
            lua
)