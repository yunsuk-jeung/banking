cmake_minimum_required(VERSION 3.14)
project(ATM VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

option(BUILD_TEST "Build test" OFF)

if(BUILD_TEST)
  add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/test ${CMAKE_BINARY_DIR}/test)
endif()

add_executable(ATM main.cpp)

file(GLOB SRC src)
target_include_directories(ATM PUBLIC include)
target_sources(ATM PUBLIC ${SRC})