cmake_minimum_required(VERSION 3.27)
project(HashTable)

set(CMAKE_CXX_STANDARD 17)

add_executable(main src/main.cpp
        src/modules/Node.cpp
        src/modules/Node.h
        src/modules/HashTable.cpp
        src/modules/HashTable.h)

add_executable(research src/research.cpp
        src/modules/Node.cpp
        src/modules/Node.h
        src/modules/HashTable.cpp
        src/modules/HashTable.h)

add_subdirectory(libs/googletest)
include_directories(libs/googletest/googletest/include)
add_executable(tests src/tests.cpp
        src/modules/Node.cpp
        src/modules/Node.h
        src/modules/HashTable.cpp
        src/modules/HashTable.h)
target_link_libraries(tests gtest)
