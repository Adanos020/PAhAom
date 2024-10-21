if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(
    PAhAom_Script
        VERSION 0.1
        DESCRIPTION "Scripting engine for PAhAom: a 2D game engine."
        LANGUAGES CXX
)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${PROJECT_SOURCE_DIR}/../Engine/include)
include_directories(${PROJECT_SOURCE_DIR}/../Util/include)

set(SCRIPT_SOURCES ${PROJECT_SOURCE_DIR}/src/Script/*.cpp ${PROJECT_SOURCE_DIR}/src/*.cpp)
set(SCRIPT_HEADERS ${PROJECT_SOURCE_DIR}/include/Script/*.hpp)

file(GLOB_RECURSE SOURCES ${SCRIPT_SOURCES} ${SCRIPT_HEADERS})
add_library(Pahaom_Script ${SOURCES})
