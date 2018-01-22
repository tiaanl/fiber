
add_executable(TCPClient "src/TCPClient.cpp")
target_link_libraries(TCPClient PUBLIC fiber)
set_property(TARGET TCPClient PROPERTY CXX_STANDARD 14)
