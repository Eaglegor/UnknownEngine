set(TARGET_NAME DEP_CEGUI)

message(STATUS "Downloading CeGUI package")
file(
	DOWNLOAD
	http://downloads.sourceforge.net/project/crayzedsgui/CEGUI%20Mk-2/0.8/cegui-0.8.4.zip
	${CMAKE_CURRENT_BINARY_DIR}/cegui-0.8.4.zip
	EXPECTED_MD5 d56b5320826318ca52fcbd939fd74e69
	SHOW_PROGRESS
	)
	
add_custom_target(${TARGET_NAME})