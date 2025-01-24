# Gather all the source files manually
SRC = $(wildcard ../../src/*.cpp ../../src/*/*.cpp ../../src/*/*/*.cpp ../../src/*/*/*/*.cpp)
VENDORS_C = $(wildcard ../include/glad/glad.c)
VENDORS_CPP = $(wildcard ../include/im3d/im3d.cpp ../include/imgui/imgui.cpp ../include/imgui/imgui_draw.cpp ../include/imgui/imgui_tables.cpp ../include/imgui/imgui_widgets.cpp ../include/imgui/imgui_impl_glfw.cpp ../include/imgui/imgui_impl_opengl3.cpp)

BUILD_DIR = ../../SIN2024/x64/Linear
OBJ = $(SRC:../../src/%.cpp=$(BUILD_DIR)/%.obj) \
      $(VENDORS_CPP:../include/%.cpp=$(BUILD_DIR)/%.obj) \
      $(VENDORS_C:../include/%.c=$(BUILD_DIR)/%.obj)
DEPS = $(OBJ:.obj=.d)  # Dependency files

# Include and library directories
INCLUDE = -I../include
LIBS = -L../lib -lglfw3dll -lassimp

# Compilers
CXX = clang++
CC = clang

# Compiler and linker flags
CXXFLAGS = -g --std=c++20 -MMD -MP $(INCLUDE)  # Add -MMD -MP
CFLAGS = -g -MMD -MP $(INCLUDE)  # Add -MMD -MP

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

$(BUILD_DIR)/%.obj: ../include/%.c
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
	@echo "Compiling C file $< -> $@"
	$(CC) $(CFLAGS) -c "$<" -o "$@"

# Rule to link the final executable
main: $(OBJ)
	$(CXX) -o main $(OBJ) $(LIBS)

# Clean up object files and the executable
clean:
	rm -rf $(BUILD_DIR)

# Include dependency files if they exist
-include $(DEPS)
