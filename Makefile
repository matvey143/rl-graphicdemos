LDFLAGS = '-Wl,-rpath,$$ORIGIN' -L./ -I./ -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
CFLAGS =

all: star-balls stars2d stars-cpp oldZunLogo raindrops
star-balls:
	$(CXX) -o star-balls star-balls.cpp $(LDFLAGS) $(CFLAGS)
stars2d:
	$(CC) -o stars2d stars2d.c $(LDFLAGS) $(CFLAGS)
stars-cpp:
	$(CXX) -o stars-cpp stars-c++.cpp $(LDFLAGS) $(CFLAGS)
oldZunLogo:
	$(CC) -o oldZunLogo oldZunLogo.c $(LDFLAGS) $(CFLAGS)
raindrops:
	$(CC) -o raindrops raindrops.c $(LDFLAGS) $(CFLAGS)
