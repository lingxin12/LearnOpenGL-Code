# Usage

## windows10:

- mkdir build && cd build && cmake .. && make

## linux:

- g++ -o out src/main.cpp src/glad.c -Iinclude -lglfw3 -lGL -lm -lXrandr -lXi -lX11 -lXxf86vm -lpthread -ldl -lXinerama -lXcursor