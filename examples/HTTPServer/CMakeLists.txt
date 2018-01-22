
set(HTTPServer_SOURCE_FILES
    "src/TCPServer.cpp"
    )

add_executable(HTTPServer ${HTTPServer_SOURCE_FILES})
target_link_libraries(HTTPServer fiber)
set_property(TARGET HTTPServer PROPERTY CXX_STANDARD 11)
