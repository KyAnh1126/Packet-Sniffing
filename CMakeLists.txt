cmake_minimum_required(VERSION 3.10)

project(packet_learning
	VERSION 1.0)
	
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src/network/network_interface)
add_subdirectory(src/UI/network/network_interface)
add_subdirectory(src/network/packet/get_packet)
add_subdirectory(src/UI/network/packet)

add_executable(output src/main.cpp)

target_link_libraries(output PRIVATE network_interface_lib display_network_interfaces_lib get_packet_lib display_packet_lib)






