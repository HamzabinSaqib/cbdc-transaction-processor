cmake_minimum_required(VERSION 3.20.x)

# Project name and version
project(FYP VERSION 1.0)

# Add the /usr/local/include (or `/your/installation/path`) directory to the include path
include_directories(/usr/local/include)

find_package(Boost COMPONENTS system thread REQUIRED)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add your source files
add_executable(transmit transmit.cpp)
add_executable(listen listen.cpp)