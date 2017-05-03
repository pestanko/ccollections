project(cdyn_collections)
cmake_minimum_required (VERSION 3.0)

set(CMAKE_C_FLAGS "-std=c11 -Wall -Wextra -pedantic -ggdb3")

file(GLOB SOURCES "src/*.c")
file(GLOB TEST_SOURCES "tests/*.c")

add_executable(collection_test ${SOURCES} ${TEST_SOURCES})


