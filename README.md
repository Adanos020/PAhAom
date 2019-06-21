# About
PAhAom is an open-source 2D game engine sans any graphical editor - everything is programmable exclusively using Lua scripts.

# Build
To build the project you'll need:
- any C++ compiler that supports C++20 standard
- [SFML](https://github.com/SFML/SFML) and [Lua](https://github.com/lua/lua)
- CMake 3.1 or newer
- Make
Make sure that the required libraries have all its headers in an appropriate for your compiler `include` directory, and compiled lib files in `lib`.

First clone the repository and the submodules:
```bash
$ git clone https://github.com/Adanos020/PAhAom
$ git submodule init
$ git submodule update --recursive
```

Then generate the Makefile and run it:
```bash
$ cmake -B build
$ cd build
$ make -j
```

# To-do list (in an arbitrary order)
- physics engine
- audio system
- shaders
- view (camera) manipulation and viewports
- multiple language support (dictionaries)
- noise functions
- more graphical objects
- manipulation of graphical objects
- better support for rect tile map
- GUI library