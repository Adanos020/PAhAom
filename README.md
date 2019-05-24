# About
PAhAom is an open-source 2D game engine sans any graphical editor - everything is programmable exclusively using Lua scripts.

# Build
To build the project you'll need:
- any C++ compiler that supports C++17 standard
- [SFML](https://github.com/SFML/SFML/) added to your PATH environment variable
- CMake 3.1 or newer
- Make

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