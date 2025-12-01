cmake_minimum_required(VERSION 3.21)
project(Delivery)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Використовувати новий пошук Python замість FindPythonLibsNew.cmake
set(PYBIND11_FINDPYTHON ON)

# Знайти Python коректно
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

include(FetchContent)

FetchContent_Declare(
    pybind11
    GIT_REPOSITORY https://github.com/pybind/pybind11.git
    GIT_TAG v2.11.1
)

FetchContent_MakeAvailable(pybind11)

file(GLOB PROJECT_SOURCES cpp/src/*.cpp)

add_executable(Delivery
    cpp/main.cpp
    ${PROJECT_SOURCES}
)

target_include_directories(Delivery PRIVATE cpp/include)

pybind11_add_module(delivery MODULE
    python/bindings.cpp
    ${PROJECT_SOURCES}
)

target_include_directories(delivery PRIVATE cpp/include)
