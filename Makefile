LDFLAGS = '-Wl,-rpath,$$ORIGIN' -L./ -I./ -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
CFLAGS =
CXXFLAGS = 

all: star-balls stars2d stars-cpp oldZunLogo raindrops current-time

star-balls: raylib.h libraylib.so star-balls.o
	$(CXX) -o star-balls star-balls.o $(LDFLAGS)
star-balls.o: raylib.h libraylib.so star-balls.cpp
	$(CXX) -c -o star-balls.o $(CFLAGS) $(CXXFLAGS) star-balls.cpp

stars2d: raylib.h libraylib.so stars2d.o
	$(CC) -o stars2d stars2d.o $(LDFLAGS)
stars2d.o: raylib.h libraylib.so stars2d.c
	$(CC) -c -o stars2d.o $(CFLAGS) stars2d.c

stars-cpp: raylib.h libraylib.so stars-cpp.o
	$(CXX) -o stars-cpp stars-cpp.o $(LDFLAGS)
stars-cpp.o: raylib.h libraylib.so stars-c++.cpp
	$(CXX) -c -o stars-cpp.o $(CFLAGS) $(CXXFLAGS) stars-c++.cpp

oldZunLogo: raylib.h libraylib.so oldZunLogo.o
	$(CC) -o oldZunLogo oldZunLogo.o $(LDFLAGS)
oldZunLogo.o: raylib.h libraylib.so oldZunLogo.c
	$(CC) -c -o oldZunLogo.o $(CFLAGS) oldZunLogo.c

raindrops: raylib.h libraylib.so raindrops.o
	$(CC) -o raindrops raindrops.o $(LDFLAGS)
raindrops.o: raylib.h libraylib.so raindrops.c
	$(CC) -c -o raindrops.o $(CFLAGS) raindrops.c

current-time: raylib.h libraylib.so current-time.o
	$(CC) -o current-time current-time.o $(LDFLAGS)
current-time.o: raylib.h libraylib.so star-balls.cpp
	$(CC) -c -o current-time.o $(CFLAGS) current-time.c
