cmake_minimum_required(VERSION 3.10)

project(2x2_solver C)

set(EXECUTABLE_NAME "main")

add_subdirectory(libs/data-structures)

add_executable(${EXECUTABLE_NAME}
    src/main.c
    src/permutations/permutations.c
    src/cube/cube.c
    src/solving/solving.c
)

target_link_libraries(${EXECUTABLE_NAME} data-structures)