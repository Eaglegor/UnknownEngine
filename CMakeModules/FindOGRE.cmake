    # Find OGRE includes and library
    #
    # This module defines
    # OGRE_INCLUDE_DIRS
    # OGRE_LIBRARIES, the libraries to link against to use OGRE.
    # OGRE_LIBRARY_DIRS, the location of the libraries
    # OGRE_FOUND, If false, do not try to use OGRE
    #
    # Copyright © 2007, Matt Williams
    #
    # Redistribution and use is allowed according to the terms of the BSD license.
    # For details see the accompanying COPYING-CMAKE-SCRIPTS file.
    IF (OGRE_LIBRARIES AND OGRE_INCLUDE_DIRS)
    SET(OGRE_FIND_QUIETLY TRUE) # Already in cache, be silent
    ENDIF (OGRE_LIBRARIES AND OGRE_INCLUDE_DIRS)
    IF (WIN32) #Windows
    MESSAGE(STATUS "Looking for OGRE")
    SET(OGRESDK $ENV{OGRE_HOME})
    SET(OGRESOURCE $ENV{OGRE_SRC})
    IF (OGRESDK)
    MESSAGE(STATUS "Using OGRE SDK")
    STRING(REGEX REPLACE "[\\]" "/" OGRESDK "${OGRESDK}")
    SET(OGRE_INCLUDE_DIRS ${OGRESDK}/include/OGRE)
    SET(OGRE_LIBRARY_DIRS ${OGRESDK}/lib)


	if(WIN32)
		if(CMAKE_BUILD_TYPE MATCHES Debug)
			FIND_PATH(OGRE_BINARY_DIR OgreMain_d.dll ${OGRESDK}/bin/Debug)
		else()
			FIND_PATH(OGRE_BINARY_DIR OgreMain.dll ${OGRESDK}/bin/Release ${OGRESDK}/bin)
		endif()
	endif(WIN32)
	
    SET(OGRE_LIBRARIES debug OgreMain_d optimized OgreMain)
    ENDIF (OGRESDK)
    IF (OGRESOURCE)
    MESSAGE(STATUS "Using OGRE built from source")
    SET(OGRE_INCLUDE_DIRS $ENV{OGRE_SRC}/OgreMain/include/OGRE)
    SET(OGRE_LIBRARY_DIRS $ENV{OGRE_SRC}/lib)

	if(WIN32)
		if(CMAKE_BUILD_TYPE MATCHES Debug)
			FIND_PATH(OGRE_BINARY_DIR OgreMain_d.dll $ENV{OGRE_SRC}/bin/Debug)
		else()
			FIND_PATH(OGRE_BINARY_DIR OgreMain.dll $ENV{OGRE_SRC}/bin/Release $ENV{OGRE_SRC}/bin)
		endif()
	endif(WIN32)

    SET(OGRE_LIBRARIES debug OgreMain_d optimized OgreMain)
    ENDIF (OGRESOURCE)
    ELSE (WIN32) #Unix
    CMAKE_MINIMUM_REQUIRED(VERSION 2.4.7 FATAL_ERROR)
    FIND_PACKAGE(PkgConfig)
    PKG_SEARCH_MODULE(OGRE OGRE)
    SET(OGRE_INCLUDE_DIRS ${OGRE_INCLUDE_DIRSS})
    SET(OGRE_LIBRARY_DIRS ${OGRE_LIBDIR})
    SET(OGRE_LIBRARIES ${OGRE_LIBRARIES} CACHE STRING "")
    ENDIF (WIN32)
    #Do some preparation
    SEPARATE_ARGUMENTS(OGRE_INCLUDE_DIRS)
    SEPARATE_ARGUMENTS(OGRE_LIBRARIES)
    SET(OGRE_INCLUDE_DIRS ${OGRE_INCLUDE_DIRS} CACHE PATH "")
    SET(OGRE_LIBRARIES ${OGRE_LIBRARIES} CACHE STRING "")
    SET(OGRE_LIBRARY_DIRS ${OGRE_LIBRARY_DIRS} CACHE PATH "")
    IF (OGRE_INCLUDE_DIRS AND OGRE_LIBRARIES)
    SET(OGRE_FOUND TRUE)
    ENDIF (OGRE_INCLUDE_DIRS AND OGRE_LIBRARIES)
    IF (OGRE_FOUND)
    IF (NOT OGRE_FIND_QUIETLY)
    MESSAGE(STATUS " libraries : ${OGRE_LIBRARIES} from ${OGRE_LIBRARY_DIRS}")
    MESSAGE(STATUS " includes : ${OGRE_INCLUDE_DIRS}")
    ENDIF (NOT OGRE_FIND_QUIETLY)
    ELSE (OGRE_FOUND)
    IF (OGRE_FIND_REQUIRED)
    MESSAGE(FATAL_ERROR "Could not find OGRE")
    ENDIF (OGRE_FIND_REQUIRED)
    ENDIF (OGRE_FOUND)
