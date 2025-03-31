cmake_minimum_required(VERSION 4.0)
project(sage)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES false "src/*.cpp")
file(GLOB_RECURSE HEADERS LIST_DIRECTORIES false "src/*.h" "src/*.hpp")
add_executable(sage ${SOURCES} ${HEADERS})
