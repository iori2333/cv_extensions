cmake_minimum_required(VERSION 3.4...3.18)
project(cv_extensions)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV CONFIG REQUIRED)

file(GLOB_RECURSE SRC_FILES cvext/*.cpp)

add_subdirectory(pybind11)

add_library(cvext_lib SHARED ${SRC_FILES})
target_link_libraries(cvext_lib PUBLIC ${OpenCV_LIBS})
target_include_directories(cvext_lib PUBLIC ${OpenCV_INCLUDE_DIRS} cvext/)

pybind11_add_module(cv_extensions src/module.cpp)
target_link_libraries(cv_extensions PRIVATE cvext_lib)
# target_include_directories(cv_extensions PRIVATE ${OpenCV_INCLUDE_DIRS})

# EXAMPLE_VERSION_INFO is defined by setup.py and passed into the C++ code as a
# define (VERSION_INFO) here.
target_compile_definitions(cv_extensions
                           PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO})
