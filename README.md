# Client-Server Chat Application
This project is a client-server chat application built using C++ and wxWidgets.

## Cloning the Repository

First, clone the repository and its submodules:

```sh
git clone --recurse-submodules https://github.com/PauloMaced0/client-server-chat-app.git
cd client-server-chat-app
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
cmake --build build
```

## Project Structure 

- `src/`: Contains the source files for the application.
- `lib/`: Contains the library source files.
- `include/`: Contains the header files.
- `libs/wxWidgets/`: Contains the wxWidgets submodule.
- `build/`: Directory where the build files and executables will be generated.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
