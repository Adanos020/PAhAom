cmake_minimum_required(VERSION 3.1...3.13)

if (${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(PAhAom VERSION 0.1
               DESCRIPTION "My first rogue-like game."
               LANGUAGES CXX)


# UTILITIES

set(UTIL_SOURCES "src/util/*.cpp")
set(UTIL_HEADERS "include/util/*.hpp")

file(GLOB_RECURSE SOURCES ${UTIL_SOURCES} ${UTIL_HEADERS})
add_library(util STATIC ${SOURCES})

target_include_directories(util PUBLIC include)

set_target_properties(util PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)


# MAIN EXEC

set(PAHAOM_SOURCES "src/PAhAom/*.cpp")
set(PAHAOM_HEADERS "include/PAhAom/*.hpp")

file(GLOB_RECURSE SOURCES ${PAHAOM_SOURCES} ${PAHAOM_HEADERS})
add_executable(pahaom ${SOURCES})

target_include_directories(pahaom PUBLIC include)
target_link_libraries(pahaom PUBLIC sfml-graphics-d
                                    sfml-window-d
                                    sfml-audio-d
                                    sfml-system-d
                                    util)

set_target_properties(pahaom PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)