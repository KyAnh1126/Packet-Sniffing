add_library(display_network_interfaces_lib)

target_sources(display_network_interfaces_lib
	PRIVATE 
		display_network_interfaces.cpp
)

target_include_directories(display_network_interfaces_lib PUBLIC ${CMAKE_SOURCE_DIR}/include/network/network_interface ${CMAKE_SOURCE_DIR}/include/UI/network/network_interface)
