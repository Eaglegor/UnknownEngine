set(TARGET_NAME DEP_EIGEN)

message(STATUS "Downloading Eigen package")
file(
	DOWNLOAD
	 http://bitbucket.org/eigen/eigen/get/3.2.4.tar.bz2
	${CMAKE_CURRENT_BINARY_DIR}/eigen_3.2.4.tar.bz2
	EXPECTED_MD5 4c4b5ed9a388a1e475166d575af25477
	SHOW_PROGRESS
	)
	
add_custom_target(${TARGET_NAME})