cmake_minimum_required(VERSION 3.23)
project(LocalizationZip)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib/submodule/libzip)

add_library(${PROJECT_NAME} lib/zip/zipRead.cpp lib/zip/zipRead.hpp)

target_link_libraries(${PROJECT_NAME} PUBLIC zip)