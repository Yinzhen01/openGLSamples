g++ -c loadShaders.cpp
g++ -c main.cpp
g++ main.o loadShaders.o -o test -lGL -lglut -lGLEW
