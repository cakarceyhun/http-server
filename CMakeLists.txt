cmake_minimum_required(VERSION 3.11.3)

# Set the C++ standard we will use
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_CXX_FLAGS "-O0 -ggdb")

# Add the path of the cmake files to the CMAKE_MODULE_PATH
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

project(http_server)

# Set library output path to /lib
set(LIBRARY_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/lib")

# Add project executable
add_executable(server src/main.cpp src/Socket.cpp)

target_link_libraries(server PUBLIC pthread)

