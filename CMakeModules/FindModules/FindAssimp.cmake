find_path(
	ASSIMP_INCLUDE_DIR
	assimp/metadata.h
	assimp/config.h
	assimp/defs.h
	HINTS
	$ENV{ASSIMP_SDK}
	$ENV{ASSIMP_HOME}
	$ENV{ASSIMP_ROOT}
	/usr
	/usr/local
	PATH_SUFFIXES
	include
	Include
)

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	set(ASSIMP_LIBRARY_SUFFIX "d")
endif()

if(WIN32)
	find_file(ASSIMP_SHARED_BINARY
		NAMES assimp${ASSIMP_LIBRARY_SUFFIX}.dll assimp.dll
		HINTS
		$ENV{ASSIMP_SDK}
		$ENV{ASSIMP_HOME}
		$ENV{ASSIMP_ROOT}
		PATH_SUFFIXES
		/bin
	)
endif()

find_library(ASSIMP_LIBRARY NAMES assimp${ASSIMP_LIBRARY_SUFFIX} assimp
			HINTS
			$ENV{ASSIMP_SDK}
			$ENV{ASSIMP_HOME}
			$ENV{ASSIMP_ROOT}
			/usr
			/usr/local
			PATH_SUFFIXES 
			lib
)

SET(Assimp_LIBRARIES ${ASSIMP_LIBRARY})
SET(Assimp_INCLUDE_DIRS ${ASSIMP_INCLUDE_DIR})
SET(Assimp_SHARED_BINARIES ${ASSIMP_SHARED_BINARY})

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Assimp FOUND_VAR Assimp_FOUND REQUIRED_VARS Assimp_LIBRARIES Assimp_INCLUDE_DIRS)
