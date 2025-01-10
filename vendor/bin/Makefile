# Gather all the source files manually
SRC = $(wildcard ../../src/*.cpp ../../src/*/*.cpp ../../src/*/*/*.cpp ../../src/*/*/*/*.cpp)
VENDORS = $(wildcard ../include/glad/glad.c ../include/im3d/im3d.cpp ../include/imgui/imgui.cpp ../include/imgui/imgui_draw.cpp ../include/imgui/imgui_tables.cpp ../include/imgui/imgui_widgets.cpp ../include/imgui/imgui_impl_glfw.cpp ../include/imgui/imgui_impl_opengl3.cpp)

BUILD_DIR = ../../SIN2024/x64/Linear
OBJ = $(SRC:../../src/%.cpp=$(BUILD_DIR)/%.obj) $(VENDORS:../include/%.cpp=$(BUILD_DIR)/%.obj)

# Include and library directories
INCLUDE = -I../include
LIBS = -L../lib -lglfw3dll -lassimp

# Compiler and linker flags
CXX = g++
CXXFLAGS = -g --std=c++20 $(INCLUDE)

# Main build target
all: $(OBJ) main

$(BUILD_DIR)/%.obj: ../../src/%.cpp
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
	@echo "Compiling $< -> $@"
	$(CXX) $(CXXFLAGS) -c "$<" -o "$@"

$(BUILD_DIR)/%.obj: ../include/%.cpp
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
	@echo "Compiling vendor file $< -> $@"
	$(CXX) $(CXXFLAGS) -c "$<" -o "$@"

# Rule to link the final executable
main: $(OBJ)
	$(CXX) -o main $(OBJ) $(LIBS)

# Clean up object files and the executable
clean:
	rm -rf $(BUILD_DIR)
