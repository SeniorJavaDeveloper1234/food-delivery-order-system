cmake_minimum_required(VERSION 3.21)
project(Delivery)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_subdirectory(external/pybind11)



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
