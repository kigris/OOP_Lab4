cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 17) # C++20 required
project(oop_lab) # Project name
# Find all .cpp files in Lab4 folder
file(GLOB SOURCES "Lab4/*.cpp")
# Exclude files starting with ._
list(FILTER SOURCES EXCLUDE REGEX "\\._.*$")
# Add executable target with all found sources
add_executable(${PROJECT_NAME} ${SOURCES})