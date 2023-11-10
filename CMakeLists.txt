cmake_minimum_required(VERSION 3.15) 
PROJECT ( main )

find_package(OpenCV REQUIRED )

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR})

include_directories(
        ${PROJECT_SOURCE_DIR}/core/c++/include
        ${PROJECT_SOURCE_DIR}/core/c++/src
        ${PROJECT_SOURCE_DIR}/utils/c++/include
        ${PROJECT_SOURCE_DIR}/utils/c++/src
)

file(GLOB all_SRCS
        "${PROJECT_SOURCE_DIR}/core/c++/include/*.hpp"
        "${PROJECT_SOURCE_DIR}/core/c++/src/*.cpp"
        "${PROJECT_SOURCE_DIR}/utils/c++/include/*.hpp"
        "${PROJECT_SOURCE_DIR}/utils/c++/src/*.cpp"
        )

        
add_library( ${PROJECT_NAME} SHARED ${all_SRCS})
# add_executable(  ${PROJECT_NAME} ${all_SRCS})
        
target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS})