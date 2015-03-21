set(TARGET_NAME DEP_BOOST)

message(STATUS "Downloading boost package")
file(
	DOWNLOAD
	http://downloads.sourceforge.net/project/boost/boost/1.57.0/boost_1_57_0.zip 
	${CMAKE_CURRENT_BINARY_DIR}/boost_1_57_0.zip 
	EXPECTED_MD5 5E040E578E3F0BA879DA04A1E0CD55FF
	SHOW_PROGRESS
	STATUS stat
	)
	
add_custom_target(${TARGET_NAME})

make_directory(${CMAKE_CURRENT_BINARY_DIR}/work)
add_custom_command(TARGET ${TARGET_NAME} COMMAND ${UNKNOWNENGINE_DEPS_SOURCE_DIR}/tools/unzip ARGS ${CMAKE_CURRENT_BINARY_DIR}/boost_1_57_0.zip -d ${CMAKE_CURRENT_BINARY_DIR}/work)
add_custom_command(TARGET ${TARGET_NAME} COMMAND bootstrap.bat WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/work/boost_1_57_0)
add_custom_command(TARGET ${TARGET_NAME} COMMAND b2 ARGS --toolset=msvc --build-type=complete stage WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/work/boost_1_57_0)