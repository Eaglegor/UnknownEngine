set(TARGET_NAME DEP_ANGELSCRIPT)

message(STATUS "Downloading AngelScript package")
file(
	DOWNLOAD
	http://www.angelcode.com/angelscript/sdk/files/angelscript_2.30.0.zip
	${CMAKE_CURRENT_BINARY_DIR}/angelscript_2.30.0.zip
	EXPECTED_MD5 1b0ec7ead145cbcb252d9e1ce14f490d
	SHOW_PROGRESS
	)
	
	
add_custom_target(${TARGET_NAME})