
add_executable(TCPServer "src/TCPServer.cpp")
target_link_libraries(TCPServer PUBLIC fiber)
set_property(TARGET TCPServer PROPERTY CXX_STANDARD 11)
