add_library(network_interface_lib)

target_sources(network_interface_lib
	PRIVATE 
		get_network_interfaces.cpp
)

target_include_directories(network_interface_lib PUBLIC ${CMAKE_SOURCE_DIR}/include/network/network_interface)



