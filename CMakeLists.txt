cmake_minimum_required(VERSION 3.20.x)

# Project name and version
project(FYP VERSION 1.0)

find_package(Boost COMPONENTS system REQUIRED)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add your source files
add_executable(transmit transmit.cpp)
add_executable(listen listen.cpp)

# Link any libraries your project depends on
add_library(nlohmann_json INTERFACE)
target_include_directories(nlohmann_json INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/lib)

target_include_directories(transmit PRIVATE ${Boost_INCLUDE_DIRS})
target_include_directories(listen PRIVATE ${Boost_INCLUDE_DIRS})

target_link_libraries(transmit PRIVATE ${Boost_LIBRARIES} nlohmann_json)
target_link_libraries(listen PRIVATE ${Boost_LIBRARIES} nlohmann_json)
