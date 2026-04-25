cmake_minimum_required(VERSION 3.10)
project(problem_076)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# If main.cpp exists, compile it with src.hpp
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
    add_executable(code main.cpp)
endif()
