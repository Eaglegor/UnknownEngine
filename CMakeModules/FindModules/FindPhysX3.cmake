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
endif()

macro(find_physx3_library name)

	if(MSVC)
		if(CMAKE_SIZEOF_VOID_P EQUAL 8)

			find_library(PHYSX_LIBRARY NAMES ${name}${PHYSX3_LIBRARY_SUFFIX}_x64 ${name}_x64 ${name}
						HINTS
						$ENV{PHYSX_SDK}
						$ENV{PHYSX_HOME}
						$ENV{PHYSX_ROOT}
						PATH_SUFFIXES 
						Lib/win64
						lib/win64
			)
		else()
		
			find_library(PHYSX_LIBRARY NAMES ${name}${PHYSX3_LIBRARY_SUFFIX}_x86 ${name}_x86 ${name}
						HINTS
						$ENV{PHYSX_SDK}
						$ENV{PHYSX_HOME}
						$ENV{PHYSX_ROOT}
						PATH_SUFFIXES 
						Lib/win32
						lib/win32
			)
		endif()
		
		list(APPEND LIBRARIES ${PHYSX_LIBRARY})
		
		unset(PHYSX_LIBRARY CACHE)
		
	endif(MSVC)
	
endmacro()

macro(find_physx3_cooking)
	find_physx3_library(PhysX3Cooking)
endmacro()

macro(find_physx3_component component_name)
	if(${component_name} STREQUAL "Cooking")
		find_physx3_cooking()
	endif()
endmacro(find_physx3_component)

find_physx3_library(PhysX3)

if(PhysX3_FIND_COMPONENTS)
	foreach(component ${PhysX3_FIND_COMPONENTS})
		find_physx3_component(${component})
	endforeach()
endif()

SET(PhysX3_LIBRARIES ${LIBRARIES})
SET(PhysX3_INCLUDE_DIRS ${PHYSX3_INCLUDE_DIR})

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(PhysX3 REQUIRED_VARS PhysX3_LIBRARIES PhysX3_INCLUDE_DIRS)