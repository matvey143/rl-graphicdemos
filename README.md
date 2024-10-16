# rl-graphicgemos
Collection of small graphical programs I made using raylib. I made a typo when making name of this repo, oops.
# Contents
1. stars2d.c - From the center of window a lot of colorful (or colorless) balls come out with random speed and random angle. You can resize window and press spacebar to change color mode.
1.1. stars-c++.cpp - basically the same as previous program but with few C++ featrues.
2. star-balls - 3d remake of stars. Now huge stars fly straight into camera, woah.
# Building
Right now only Linux is supported.
You need to add header and library files into this directory from latest release of raylib and run make. Dynamic linking is prefered because building produces few small executables all depending on the same library. So build process can look like this:
```
cd rl-graphicgemos
cp <directory with header files>/*.h ./
cp <directory with library files>/*.so* ./
make
```
Alternatively you can link with library and header files somethere else but you would need to edit Makefile to do so.
# TODO
- Clean up code (especially star-balls.cpp);
- Add Windows support;
- More demos?
# Special thanks
- [raysan5](github.com/raysan5) for developing [raylib](raylib.com), graphical library I used for this project. Raylib is a zlib licensed software. Read more at raylib-license.txt;
- GitHub user [Sieep-coding](github.com/Sieep-coding). His GitHub repo [snow-simulation](github.com/Sieep-coding/snow-simulation) inspired this project;
- User baz from Stack Overflow. I used his [implementation of random float number generation](https://stackoverflow.com/a/44105089);
# Note
**Warning**: I am no medical expert, but it looks like these programs can potentialy trigger seizures for people with photosensitive epilepsy.
