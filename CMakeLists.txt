cmake_minimum_required(VERSION 3.8)

project(fiber)

# Dependencies

include("cmake/nucleus.cmake")

set(fiber_HEADER_FILES
    "include/fiber/SocketHandle.h"
    "include/fiber/Socket.h"
    "include/fiber/ClientSocket.h"
    "include/fiber/IpAddress.h"
    "include/fiber/Endpoint.h"
    "include/fiber/Resolver.h"
    "include/fiber/Win/Winsock.h"
    "include/fiber/ClientSocketTCP.h"
    )

set(fiber_SOURCE_FILES
    "src/Socket.cpp"
    "src/ClientSocket.cpp"
    "src/Endpoint.cpp"
    "src/IpAddress.cpp"
    "src/Resolver.cpp"
    "src/Win/Winsock.cpp"
    "src/ClientSocketTCP.cpp"
    )

add_library(fiber ${fiber_HEADER_FILES} ${fiber_SOURCE_FILES})
target_link_libraries(fiber PUBLIC nucleus)
if(WIN32)
    target_link_libraries(fiber PUBLIC "Ws2_32")
endif()
target_include_directories(fiber PUBLIC "include")

set(fiber_TEST_FILES
    "tests/SocketTests.cpp"
    "tests/IpAddressTests.cpp"
    "tests/ResolverTests.cpp"
    "tests/ClientSocketTCPTests.cpp"
    )

add_executable(FiberTests ${fiber_TEST_FILES})
target_link_libraries(FiberTests PUBLIC fiber catch2)

add_subdirectory("external" "external")
