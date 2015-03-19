set(TARGET_NAME DEP_SDL2)

message(STATUS "Downloading SDL2 package")
file(
	DOWNLOAD
	https://www.libsdl.org/release/SDL2-2.0.3.zip
	${CMAKE_CURRENT_SOURCE_DIR}/SDL2-2.0.3.zip
	EXPECTED_MD5 55f1eae5142d20db11c844d8d4d6deed
	SHOW_PROGRESS
	)

add_custom_target(${TARGET_NAME})