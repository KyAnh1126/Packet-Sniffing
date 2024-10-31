add_library(get_packet_lib)

target_sources(get_packet_lib
	PRIVATE 
		get_packet.cpp
)

target_include_directories(get_packet_lib PUBLIC ${CMAKE_SOURCE_DIR}/include/network/packet ${CMAKE_SOURCE_DIR}/include/UI/network/packet)
	
