cmake_minimum_required(VERSION 4.0.0)
project(monitor CXX)

file(GLOB SRC_FILES 
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/*.h")

file(GLOB SLINT_FILES "${CMAKE_SOURCE_DIR}/ui/*.slint")

find_package(Slint REQUIRED)

add_executable(monitor ${SRC_FILES})

slint_target_sources(monitor ${SLINT_FILES})

add_subdirectory("${CMAKE_SOURCE_DIR}/lib_sys")
add_subdirectory("${CMAKE_SOURCE_DIR}/Graph")

target_link_libraries(monitor PRIVATE Slint::Slint lib_sys Graph)

set_directory_properties(EXECUTABLE_OUTPUT_PATH DEBUG_CONFIGURATIONS "${CMAKE_SOURCE_DIR}/build/debug")