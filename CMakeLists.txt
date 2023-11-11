cmake_minimum_required(VERSION 3.15) 
PROJECT ( main )

find_package(OpenCV REQUIRED )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++20")

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR})

include_directories(
        ${PROJECT_SOURCE_DIR}/Tracker/c++/include
        ${PROJECT_SOURCE_DIR}/Tracker/c++/src

)

file(GLOB all_SRCS
        "${PROJECT_SOURCE_DIR}/Tracker/c++/include/*.hpp"
        "${PROJECT_SOURCE_DIR}/Tracker/c++/src/*.cpp"

        )

        
# add_library( ${PROJECT_NAME} SHARED ${all_SRCS})
add_executable(  ${PROJECT_NAME} ${all_SRCS})
        
target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS})