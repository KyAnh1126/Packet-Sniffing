add_library(display_packet_lib)

target_sources(display_packet_lib
	PRIVATE 
		display_packet.cpp
)

target_include_directories(display_packet_lib PUBLIC ${CMAKE_SOURCE_DIR}/include/UI/network/packet ${CMAKE_SOURCE_DIR}/include/network/packet)
	
