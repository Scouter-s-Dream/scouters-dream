set(CMAKE_C_COMPILER "/usr/bin/gcc-11")
set(CMAKE_CXX_COMPILER "/usr/bin/g++-11")

cmake_minimum_required(VERSION 3.15) 
PROJECT ( Tracker )

find_package(OpenCV REQUIRED )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++20 -Wno-undef -O3 -W")


include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR})

include_directories(
        ${PROJECT_SOURCE_DIR}/c++/include
        ${PROJECT_SOURCE_DIR}/c++/src

)

file(GLOB all_SRCS
        "${PROJECT_SOURCE_DIR}/c++/include/*.hpp"
        "${PROJECT_SOURCE_DIR}/c++/src/*.cpp"

        )

        
add_library( ${PROJECT_NAME} SHARED ${all_SRCS})
# add_executable(  ${PROJECT_NAME} ${all_SRCS})
         
target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS})