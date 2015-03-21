set(TARGET_NAME DEP_OGRE)

message(STATUS "Downloading Ogre package")
file(
	DOWNLOAD
	https://bitbucket.org/sinbad/ogre/get/v1-9-0.zip
	${CMAKE_CURRENT_SOURCE_DIR}/ogre_1.9.0.zip
	EXPECTED_MD5 6e5a5097648b75ac0cc740397d0117fd
	SHOW_PROGRESS
	)

add_custom_target(${TARGET_NAME})

add_dependencies(${TARGET_NAME} DEP_BOOST)