cmake_minimum_required(VERSION 3.9)

project(fiber)

# Dependencies

include("cmake/nucleus.cmake")

set(fiber_HEADER_FILES
    "include/fiber/Socket.h"
)

set(fiber_SOURCE_FILES
    "src/Socket.cpp"
)

add_library(fiber ${fiber_HEADER_FILES} ${fiber_SOURCE_FILES})
target_include_directories(fiber PUBLIC "include")

set(fiber_TEST_FILES
    "tests/SocketTests.cpp"
)

add_executable(FiberTests ${fiber_TEST_FILES})
target_link_libraries(FiberTests PUBLIC fiber catch2)

add_subdirectory("external" "external")
