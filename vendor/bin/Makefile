# Gather all the source files manually
SRC = $(wildcard ../../src/*.cpp ../../src/*/*.cpp ../../src/*/*/*.cpp ../../src/*/*/*/*.cpp)
OBJ = $(SRC:.cpp=.o)

# Include and library directories
INCLUDE = -I../include -I../../src
LIBS = -L../lib -lglfw3dll -lassimp

# Main build target
all: main

main: $(SRC)
	g++ -g --std=c++20 $(INCLUDE) $(SRC) ../../src/glad.c -o main $(LIBS)

# Clean up object files and the executable
clean:
	rm -f $(OBJ) main