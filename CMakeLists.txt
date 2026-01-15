cmake_minimum_required(VERSION 3.16)
project(sda_lab4 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ------------------------------------------------------------
# Patterns
# ------------------------------------------------------------

add_executable(adapter adapter/main.cpp)
add_executable(builder builder/main.cpp)
add_executable(composite composite/main.cpp)
add_executable(decorator decorator/main.cpp)
add_executable(dependencyinjection dependencyinjection/main.cpp)
add_executable(facade facade/main.cpp)
add_executable(factory factory/main.cpp)
add_executable(proxy proxy/main.cpp)
add_executable(singleton singleton/main.cpp)
