cmake_minimum_required(VERSION 3.0) # CMake version required
set(CMAKE_CXX_STANDARD 17) # C++20 required
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++2a") # set the C++ dialect

# If CMakeCache.txt does not exist, set build type to Release
#if(NOT EXISTS ${CMAKE_BINARY_DIR}/CMakeCache.txt)
# If build type is not specified, set it to Release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
#endif()

# IUf build type is Debug, set output directory to debug
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/debug") # Create debug directory
    # Set output directory to debug
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/debug")
    add_definitions(-DDEBUG) # Add DEBUG macro
else()
    #add_definitions(-DRELEASE) # Add RELEASE macro, not needed
    file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/release") # Create release directory
    # Set output directory to release
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/release")
endif()

project(oop_lab) # Project name
# Find all .cpp files in Lab4 folder
file(GLOB SOURCES "Lab4/*.cpp")
# Exclude files starting with ._
list(FILTER SOURCES EXCLUDE REGEX "\\._.*$")
# Add executable target with all found sources
add_executable(${PROJECT_NAME} ${SOURCES})