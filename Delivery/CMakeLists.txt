cmake_minimum_required(VERSION 3.15)
project(Delivery LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

# --- Підтягнути pybind11 ---
include(FetchContent)
FetchContent_Declare(
    pybind11
    GIT_REPOSITORY https://github.com/pybind/pybind11.git
    GIT_TAG v2.11.1
)
FetchContent_MakeAvailable(pybind11)

# --- Шлях до include ---
include_directories(cpp/include)

# --- Зібрати всі .cpp файли ---
file(GLOB SOURCES cpp/src/*.cpp)

# --- Екзешник ---
add_executable(Delivery
    cpp/main.cpp
    ${SOURCES}
)

# --- Python модуль ---
pybind11_add_module(delivery MODULE
    cpp/src/bindings.cpp   # твій pybind файл
    ${SOURCES}              # логіка програми
)

# Забороняємо видаляти .pyd після установки
set_target_properties(delivery PROPERTIES
    OUTPUT_NAME "delivery"
)
