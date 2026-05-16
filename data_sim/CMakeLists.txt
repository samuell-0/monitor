cmake_minimum_required(VERSION 4.0.0)
project(data_sim C)

add_library(data_sim STATIC)

target_include_directories(data_sim PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_sources(data_sim PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c
)

add_executable(test_data_sim test.c)

target_link_libraries(test_data_sim PRIVATE data_sim)
