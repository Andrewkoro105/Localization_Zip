cmake_minimum_required(VERSION 3.23)
project(LocalizationZip)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(
        zip
        GIT_REPOSITORY https://github.com/nih-at/libzip.git
        GIT_TAG v1.9.2
        FIND_PACKAGE_ARGS NAMES zip
)

FetchContent_MakeAvailable(zip)

add_library(${PROJECT_NAME} MODULE lib/zip/zipRead.cpp lib/zip/zipRead.hpp)

target_link_libraries(${PROJECT_NAME} PUBLIC zip)