set(TARGET_NAME DEP_ASSIMP)

message(STATUS "Downloading Assimp package")
file(
	DOWNLOAD
	http://downloads.sourceforge.net/project/assimp/assimp-3.1/assimp-3.1.1.zip
	${CMAKE_CURRENT_BINARY_DIR}/assimp-3.1.1.zip
	EXPECTED_MD5 b16774ddd1068199fc620cd41156d01d
	SHOW_PROGRESS
	)
	
add_custom_target(${TARGET_NAME})