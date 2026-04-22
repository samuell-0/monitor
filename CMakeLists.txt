cmake_minimum_required(VERSION 4.0.0)
project(monitor CXX)

find_package(Slint REQUIRED)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/lib_sys")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Graph")

add_executable(monitor
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

slint_target_sources(monitor 
    ${CMAKE_CURRENT_SOURCE_DIR}/ui/main.slint
)

target_link_libraries(monitor PRIVATE Slint::Slint lib_sys)

set_directory_properties(EXECUTABLE_OUTPUT_PATH DEBUG_CONFIGURATIONS "${CMAKE_CURRENT_SOURCE_DIR}/build/debug")