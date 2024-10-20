# About
PAhAom is an open-source 2D game engine without a graphical editor - everything is programmable exclusively using Lua scripts.

# Build
To build the project you'll need:
- any C++ compiler that supports C++20
- [Lua](https://github.com/lua/lua)
- CMake 3.1 or newer
- Make

Make sure that the required libraries have all its headers in an appropriate for your compiler `include` directory, and compiled lib files in `lib`.

First clone the repository and the submodules:
```bash
$ git clone --recurse-submodules git@github.com:Adanos020/PAhAom.git
```

Then generate the Makefile and run it:
```bash
$ cmake -B build
$ cd build
$ make -j
```

To run the game, return to the project's root directory and simply run the executable:
```bash
$ cd ..
$ build/Pahaom
```

# To-do list (the order is arbitrary)
- physics engine
- audio system
- shaders
- better system for scene management
- view (camera) manipulation and viewports
- multiple language support (dictionaries)
- noise functions
- more graphical objects and animations
- manipulation of graphical objects
- better support for tile maps
- GUI library