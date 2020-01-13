cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

set(CMAKE_CXX_FLAGS "-std=c++11")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(FrenetSol)

set(SOURCE_FILES
    NumericalMethods.cpp
    Core.cpp
    Driver.cpp
    IO.cpp
)

set(HEADER_FILES
    NumericalMethods.h
    Core.h
    Util.h
    IO.h
)

find_package (Eigen3 3.3 REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/..")

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(${PROJECT_NAME} stdc++fs Eigen3::Eigen)


