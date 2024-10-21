if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(
    Pahaom_Util
        VERSION 0.1
        DESCRIPTION "Utility library for PAhAom: a 2D game engine."
        LANGUAGES CXX
)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${PROJECT_SOURCE_DIR}/../Script/include)

set(UTIL_SOURCES ${PROJECT_SOURCE_DIR}/src/Util/*.cpp)
set(UTIL_HEADERS ${PROJECT_SOURCE_DIR}/include/Util/*.hpp)

file(GLOB_RECURSE SOURCES ${UTIL_SOURCES} ${UTIL_HEADERS})
add_library(Pahaom_Util ${SOURCES})
