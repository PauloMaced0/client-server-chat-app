cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

project(client-server-chat-app)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(wxBUILD_SHARED OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (APPLE)
    message(STATUS "Configuring for macOS")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -O2 -Wall -Wextra -Wfatal-errors -pthread")
    elseif (CMAKE_C_COMPILER_ID STREQUAL "GNU")
        set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -O2 -Wall -Wextra -Wfatal-errors -pthread")
    endif()
elseif(UNIX AND NOT APPLE)
    message(STATUS "Configuring for Linux")
    find_package(X11)
    if(X11_FOUND)
        if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
            set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -O2 -Wall -Wextra -Wfatal-errors -pthread -lX11")
        elseif (CMAKE_C_COMPILER_ID STREQUAL "GNU")
            set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -O2 -Wall -Wextra -Wfatal-errors -pthread -lX11")
        endif()
    else()
        if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
            set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -O2 -Wall -Wextra -Wfatal-errors -pthread")
        elseif (CMAKE_C_COMPILER_ID STREQUAL "GNU")
            set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -O2 -Wall -Wextra -Wfatal-errors -pthread")
        endif()
    endif()
elseif(WIN32)
    message(STATUS "Using Windows? XD...")
endif()

add_subdirectory(libs/wxWidgets)

# Add include directories
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/libs/wxWidgets/include)

# Source files for each target
set(SRC_FILES_SERVER
    src/server.cpp
    lib/protocol.cpp
    lib/server_utils.cpp
)

set(SRC_FILES_CLIENT
    src/app.cpp
)

# Add executables
add_executable(server ${SRC_FILES_SERVER})
add_executable(app ${SRC_FILES_CLIENT})

# Link wxWidgets to the app target
target_link_libraries(app wx::net wx::core wx::base)
