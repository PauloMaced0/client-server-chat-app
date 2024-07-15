cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(client-server-chat-app)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(wxBUILD_SHARED OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if ( CMAKE_COMPILER_IS_GNUCXX )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -O2 -Wall -Wextra  -Wfatal-errors -pthread")
elseif( CMAKE_COMPILER_IS_GNUCC )
    set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -O2 -Wall -Wextra  -Wfatal-errors -pthread")
endif()

add_subdirectory(libs/wxWidgets)

# Add include directories
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/libs/wxWidgets/include)

# Source files for each target
set(SRC_FILES_SERVER
    src/main.cpp
    lib/protocol.cpp
)

# set(SRC_FILES_CLIENT
#     lib/another_main.cpp
#     lib/another_protocol.cpp
# )

set(SRC_FILES_APP
    src/app.cpp
)

# Add executables
add_executable(main ${SRC_FILES_SERVER})
# add_executable(another_main ${SRC_FILES_CLIENT})
add_executable(app ${SRC_FILES_APP})

# Link wxWidgets to the app target
target_link_libraries(app wx::net wx::core wx::base)
