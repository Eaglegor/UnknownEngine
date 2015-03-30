# - Find ogg
# Find the native ogg includes and libraries
#
# ANGELSCRIPT_INCLUDE_DIR - where to find angelscript.h, etc.
# ANGELSCRIPT_LIBRARIES - List of libraries when using angelscript.
# ANGELSCRIPT_FOUND - True if angelscript found.
if(ANGELSCRIPT_INCLUDE_DIR)
# Already in cache, be silent
	set(ANGELSCRIPT_FIND_QUIETLY TRUE)
endif(ANGELSCRIPT_INCLUDE_DIR)
if(CMAKE_BUILD_TYPE STREQUAL Debug)
	set(LIBSUFFIX "d")
endif()

find_path(ANGELSCRIPT_INCLUDE_DIR angelscript.h HINTS $ENV{ANGELSCRIPT_HOME} $ENV{ANGELSCRIPT_SDK}/angelscript $ENV{ANGELSCRIPT_ROOT} /usr/include PATH_SUFFIXES include)
# MSVC built angelscript may be named angelscript_static.
# The provided project files name the library with the lib prefix.
find_library(ANGELSCRIPT_LIBRARY NAMES angelscript${LIBSUFFIX} angelscript HINTS $ENV{ANGELSCRIPT_HOME} $ENV{ANGELSCRIPT_SDK}/angelscript $ENV{ANGELSCRIPT_ROOT} PATH_SUFFIXES lib )
# Handle the QUIETLY and REQUIRED arguments and set ANGELSCRIPT_FOUND
# to TRUE if all listed variables are TRUE.

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ANGELSCRIPT DEFAULT_MSG ANGELSCRIPT_INCLUDE_DIR ANGELSCRIPT_LIBRARY)
set(ANGELSCRIPT_LIBRARIES ${ANGELSCRIPT_LIBRARY})
set(ANGELSCRIPT_INCLUDE_DIRS ${ANGELSCRIPT_INCLUDE_DIR})
mark_as_advanced(ANGELSCRIPT_INCLUDE_DIR)
mark_as_advanced(ANGELSCRIPT_LIBRARY)