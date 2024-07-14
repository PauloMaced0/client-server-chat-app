cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(client-server-chat-app)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${PROJECT_SOURCE_DIR}/include)

# Specify the path to wxWidgets
set(wxWidgets_DIR "/Users/paulomacedo/wxWidgets-3.2.5/build-release")

# Use wx-config to get compile and linker flags
execute_process(COMMAND bash ${wxWidgets_DIR}/wx-config --cxxflags
                OUTPUT_VARIABLE WX_CXX_FLAGS
                OUTPUT_STRIP_TRAILING_WHITESPACE)

execute_process(COMMAND bash ${wxWidgets_DIR}/wx-config --libs
                OUTPUT_VARIABLE WX_LINK_FLAGS
                OUTPUT_STRIP_TRAILING_WHITESPACE)

if(WX_CXX_FLAGS STREQUAL "" OR WX_LINK_FLAGS STREQUAL "")
    message(FATAL_ERROR "wx-config did not provide necessary flags. Check wxWidgets installation or wx-config script (eg. /path/wx-config --version).")
else()
    message(STATUS "wxWidgets C++ flags: ${WX_CXX_FLAGS} \n")
    message(STATUS "wxWidgets link flags: ${WX_LINK_FLAGS} \n")
endif()

# Add compile flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WX_CXX_FLAGS}")

# Set macOS specific architecture to arm64
set(CMAKE_OSX_ARCHITECTURES "arm64")

# Add include directories manually (optional)
include_directories(${wxWidgets_ROOT_DIR}/include)

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
target_link_libraries(app ${wxWidgets_LIBRARIES})
