# Client-Server Chat Application
This project is a client-server chat application built using C++ and wxWidgets.

### General
- CMake 3.10 or higher
- A C++ compiler that supports C++17 (e.g., GCC, Clang)

### System-Specific Requirements

#### Linux
- GTK+ 3 development files
- Wayland development files (if using Wayland)
- X11 development files (if using X11)

#### macOS
- XQuartz (for X11 support, optional)
- Native macOS graphical development files are usually included with Xcode

#### Windows
- No additional graphical development files needed if using wxWidgets with native Windows support

**Note**: Ensure you have installed the development files for the graphical interfaces your system uses. For instance, on Linux, you might need to install packages like `libgtk-3-dev`, `libwayland-dev`, or `libx11-dev`.

## Cloning the Repository

First, clone the repository and its submodules:

```sh
git clone --recurse-submodules https://github.com/PauloMaced0/client-server-chat-app.git && cd client-server-chat-app
```

If you have already cloned the repository without `--recurse-submodules`, you can initialize and update the submodules with:

```sh
git submodule update --init --recursive
```

## Building the Project 

1. Create a build directory:

```sh
mkdir -p build
```

2. Configure the project with CMake:

```sh
cmake . -B build
```

3. Build the project:

```sh
cmake --build build -j [N]
```

**Note**: Executing `cmake` with the option `-j`, allows N jobs at once, infinite jobs with no argument. This optimizes build performance.

## Project Structure 

- `src/`: Contains the source files for the application.
- `lib/`: Contains the library source files.
- `include/`: Contains the header files.
- `libs/wxWidgets/`: Contains the wxWidgets submodule.
- `build/`: Directory where the build files and executables will be generated.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
