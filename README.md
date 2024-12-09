# SIN2024

Welcome to the SIN2024 repository! This project is a C++ game engine designed to provide a flexible and powerful framework for creating 3D games. It includes features such as advanced graphics rendering, input handling, and asset management.

## Features

- **Graphics Rendering**: Utilizes OpenGL with GLFW, GLAD, and Assimp for rendering and managing 3D graphics.
- **Input Handling**: Supports keyboard and mouse inputs for dynamic control.
- **Asset Management**: Handles various types of assets, including models and textures, using Assimp and other tools.
- **Modular Architecture**: Designed with a modular approach to make it easy to extend and integrate with other systems.

## Installation

### Prerequisites

- **C++20**: Ensure that you have a C++20 compatible compiler.
- **Dependencies**: The project depends on several libraries (note that all the dependencies are included in the project):
  - [GLFW](https://www.glfw.org/)
  - [GLAD](https://glad.dav1d.de/)
  - [Assimp](http://assimp.sourceforge.net/)

### Building

1. Clone the repository:

    ```bash
    git clone https://github.com/veloSecreto/SIN2024.git
    cd SIN2024
    ```

2. Build the project using `MinGW` or another suitable toolchain:

    ```bash
    # For MinGW
    cd vendor/bin
    mingw32-make
    ```

## Usage

1. Edit the `Game::start()` function in `src/game.cpp` for setting up the scene.

2. Build the project.

3. Run the `main.exe` application in the `vendor/bin` path.

## Screenshots

Captured some enthusiastic moments while developing the engine. The engine is growing very fast.

### Kernel Visualization
![Kernel](res/_screenshots/kernal.png)

### Old-School Grain Effect
![Old School Grain Effect](res/_screenshots/old%20school%20grain%20effect.png)

### Enhanced Grain Effect
![Old School Grain Effect 2](res/_screenshots/old%20school%20grain%20effect%202.png)

### G-Buffer Rendering
![G-Buffer](res/_screenshots/gbuffer.png)

## Contributing

We welcome contributions to improve the SIN2024 engine. You need to be a member of the SIN Development Department of Enigma Publishers Ltd for Contribution. If you'd like to contribute:

1. Request the Boss for Collaboration in the repository.
2. Make your desired changes.
3. Submit a copy of your changes to the Boss and then push your changes if allowed by Boss.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

## Contact

If you have any questions or need further assistance, please open an issue on the GitHub repository or contact nahmedkhan231@gmail.com for more information.

---

Thank you for checking out SIN2024! We hope it helps you in your game development journey.
