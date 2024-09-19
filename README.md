# SIN2024

Welcome to the SIN2024 repository! This project is a C++ game engine designed to provide a flexible and powerful framework for creating 3D games. It includes features such as advanced graphics rendering, input handling, and asset management.

## Features

- **Graphics Rendering**: Utilizes OpenGL with GLFW, GLAD, and Assimp for rendering and managing 3D graphics.
- **Input Handling**: Supports keyboard and mouse inputs for dynamic control.
- **Asset Management**: Handles various types of assets, including models and textures, using Assimp and other tools.
- **Modular Architecture**: Designed with a modular approach to make it easy to extend and integrate with other systems.

## Installation

### Prerequisites

- **C++17**: Ensure that you have a C++17 compatible compiler.
- **Dependencies**: The project depends on several libraries:
  - [GLFW](https://www.glfw.org/)
  - [GLAD](https://glad.dav1d.de/)
  - [Assimp](http://assimp.sourceforge.net/)

### Building

1. Clone the repository:

    ```bash
    git clone https://github.com/Noman2009-creator/SIN2024.git
    cd SIN2024
    ```

2. Install dependencies if you haven't already.

3. Build the project using `MinGW` or another suitable toolchain:

    ```bash
    # For MinGW
    mingw32-make
    ```

    If you are using CMake, ensure you have CMake installed, then run:

    ```bash
    mkdir build
    cd build
    cmake ..
    cmake --build .
    ```

## Usage

1. Compile your source code files along with the SIN2024 engine.

2. Link against the SIN2024 libraries.

3. Run your compiled application to see the engine in action.

## Contributing

We welcome contributions to improve the SIN2024 engine. If you'd like to contribute:

1. Fork the repository.
2. Create a new branch for your feature or bug fix.
3. Submit a pull request with a clear description of your changes.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

## Contact

If you have any questions or need further assistance, please open an issue on the GitHub repository or contact [your email] for more information.

---

Thank you for checking out SIN2024! We hope it helps you in your game development journey.
