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

FetchContent_Declare(
		option_result_cpp
		GIT_REPOSITORY https://github.com/Hedgehogo/option-result-cpp.git
		GIT_TAG        main
		FIND_PACKAGE_ARGS NAMES option_result_cpp
)

FetchContent_MakeAvailable(zip option_result_cpp)

add_library(${PROJECT_NAME} MODULE lib/zip/zipRead.cpp lib/zip/zipRead.hpp)

target_link_libraries(${PROJECT_NAME} PUBLIC zip option_result_cpp)