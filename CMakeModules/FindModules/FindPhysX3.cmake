find_path(
	PHYSX3_INCLUDE_DIR
	PxPhysXConfig.h
	HINTS
	$ENV{PHYSX_SDK}
	$ENV{PHYSX_HOME}
	$ENV{PHYSX_ROOT}
	PATH_SUFFIXES
	Include
	include
)

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	set(PHYSX3_LIBRARY_SUFFIX "DEBUG")
	add_definitions(-D_DEBUG)
else()
	add_definitions(-DNDEBUG)
endif()

if(WIN32)
	set(SHARED_BINARY_EXTENSION ".dll")
else()
	set(SHARED_BINARY_EXTENSION ".so")
endif()

macro(find_physx3_shared_binary name)
	
	if(CMAKE_SIZEOF_VOID_P EQUAL 8)

		find_file(PHYSX_SHARED_BINARY NAMES ${name}CHECKED_x64${SHARED_BINARY_EXTENSION} ${name}_x64${SHARED_BINARY_EXTENSION} ${name}${SHARED_BINARY_EXTENSION}
					HINTS
					$ENV{PHYSX_SDK}
					$ENV{PHYSX_HOME}
					$ENV{PHYSX_ROOT}
					PATH_SUFFIXES 
					Bin/win64
					bin/win64
					Bin/linux64
					bin/linux64
		)
		
	else()

		find_file(PHYSX_SHARED_BINARY NAMES ${name}CHECKED_x86${SHARED_BINARY_EXTENSION} ${name}_x86${SHARED_BINARY_EXTENSION} ${name}${SHARED_BINARY_EXTENSION}
					HINTS
					$ENV{PHYSX_SDK}
					$ENV{PHYSX_HOME}
					$ENV{PHYSX_ROOT}
					PATH_SUFFIXES 
					Bin/win32
					bin/win32
					Bin/linux32
					bin/linux32
		)
		
	endif()
	
	list(APPEND SHARED_BINARIES ${PHYSX_SHARED_BINARY})
	
	unset(PHYSX_SHARED_BINARY CACHE)
	
endmacro()

macro(find_physx3_library name)

	if(CMAKE_SIZEOF_VOID_P EQUAL 8)

		find_library(PHYSX_LIBRARY NAMES ${name}${PHYSX3_LIBRARY_SUFFIX}_x64 ${name}${PHYSX3_LIBRARY_SUFFIX} ${name}_x64 ${name}
					HINTS
					$ENV{PHYSX_SDK}
					$ENV{PHYSX_HOME}
					$ENV{PHYSX_ROOT}
					PATH_SUFFIXES 
					Lib/win64
					lib/win64
					Lib/linux64
					lib/linux64
		)
		
	else()

		find_library(PHYSX_LIBRARY NAMES ${name}${PHYSX3_LIBRARY_SUFFIX}_x86 ${name}${PHYSX3_LIBRARY_SUFFIX} ${name}_x86 ${name}
					HINTS
					$ENV{PHYSX_SDK}
					$ENV{PHYSX_HOME}
					$ENV{PHYSX_ROOT}
					PATH_SUFFIXES 
					Lib/win32
					lib/win32
					Lib/linux32
					lib/linux32
		)
		
	endif()
	
	list(APPEND LIBRARIES ${PHYSX_LIBRARY})
	
	unset(PHYSX_LIBRARY CACHE)
	
endmacro()

macro(find_physx3_cooking)
	find_physx3_library(PhysX3Cooking)
	find_physx3_shared_binary(PhysX3Cooking)
endmacro()

macro(find_physx3_component component_name)
	if(${component_name} STREQUAL "Cooking")
		find_physx3_cooking()
	endif()
endmacro(find_physx3_component)

find_physx3_library(PhysX3)
find_physx3_library(PhysX3Common)
find_physx3_library(PhysX3Extensions)

find_physx3_shared_binary(PhysX3)
find_physx3_shared_binary(PhysX3Common)
find_physx3_shared_binary(nvToolsExt32_1)

if(PhysX3_FIND_COMPONENTS)
	foreach(component ${PhysX3_FIND_COMPONENTS})
		find_physx3_component(${component})
	endforeach()
endif()

SET(PhysX3_LIBRARIES ${LIBRARIES})
SET(PhysX3_INCLUDE_DIRS ${PHYSX3_INCLUDE_DIR})
SET(PhysX3_SHARED_BINARIES ${SHARED_BINARIES})

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(PhysX3 FOUND_VAR PhysX3_FOUND REQUIRED_VARS PhysX3_LIBRARIES PhysX3_INCLUDE_DIRS)