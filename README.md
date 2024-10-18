# rl-graphicdemos
Collection of small graphical programs I made using raylib.
# Contents
1. stars2d.c - From the center of window a lot of colorful (or colorless) balls come out with random speed and random angle. You can resize window and press spacebar to change color mode.
2. stars-c++.cpp - basically the same as previous program but with few C++ featrues.
3. star-balls - 3d remake of stars. Now huge stars fly straight into camera, woah.
# Building from source code
I, unfortunately only know how to use GNU Make on basic level out of all build tools. If you don't want to deal with that, your best option would probably be downloading latest release from GitHub.
## Linux
You need to add header and library files into this directory from [latest release](github.com/raysan5/raylib/releases) of raylib and run make. Dynamic linking is prefered because building produces few small executables all depending on the same library. So build process can look like this:
```
cd rl-graphicdemos
cp <directory with header files>/*.h ./
cp <directory with library files>/*.so* ./
make
```
You can also add compiler flags with CFLAGS, for example like this:
```
make -j4 CFLAGS="-O2 -mtune=native -march=native"
```
## Windows
Program called [w64devkit](github.com/skeeto/w64devkit/releases) will be used for this compilation process. You will need to add raylib.dll and .h header files to this directory from [latest mingw-w64 release of raylib](github.com/raysan/raylib/releases). After that you need to run w64devkit.exe and type in following commands:
```
cd <directory where repo is located>/rl-graphicdemos
make -f Makefile-w64
```
You can also add compiler flags with CFLAGS, for example like this:
```
make -f Makefile-w64 -j4 CFLAGS="-O2 -mtune=native -march=native"
```

Alternatively you can link with library and header files somethere else but you would need to edit Makefile to do so.
# TODO
- Clean up code;
- Publish releases;
- More demos?
- More buiding options?
# Special thanks
- [raysan5](github.com/raysan5) for developing [raylib](raylib.com), graphical library I used for this project. Raylib is a zlib licensed software. Read more at raylib-license.txt;
- GitHub user [Sieep-coding](github.com/Sieep-coding). His GitHub repo [snow-simulation](github.com/Sieep-coding/snow-simulation) inspired this project;
- User baz from Stack Overflow. I used his [implementation of random float number generation](https://stackoverflow.com/a/44105089);
# Note
**Warning**: I am no medical expert, but it looks like these programs can potentialy trigger seizures for people with photosensitive epilepsy.
