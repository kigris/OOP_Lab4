cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 20) # C++20 required
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++2a")
project(oop_lab) # Project name
# Find all .cpp files in Lab4 folder
file(GLOB SOURCES "Lab4/*.cpp")
# Exclude files starting with ._
list(FILTER SOURCES EXCLUDE REGEX "\\._.*$")
# Add executable target with all found sources
add_executable(${PROJECT_NAME} ${SOURCES})