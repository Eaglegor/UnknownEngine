set(TARGET_NAME DEP_BOOST)

message(STATUS "Downloading boost package")
file(
	DOWNLOAD
	http://downloads.sourceforge.net/project/boost/boost/1.57.0/boost_1_57_0.zip 
	${CMAKE_CURRENT_SOURCE_DIR}/boost_1_57_0.zip 
	EXPECTED_MD5 5E040E578E3F0BA879DA04A1E0CD55FF
	SHOW_PROGRESS
	STATUS stat
	)
	
add_custom_target(${TARGET_NAME})