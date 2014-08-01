# Compilation

list(APPEND INCLUDED_HEADERS ${UNKNOWN_ENGINE_SOURCE_DIR}/SharedLibrariesExportHeaders)

list(APPEND SOURCES_WILDCARD "*.cxx" "*.cpp" "*.hpp" "*.h")
file(GLOB_RECURSE SOURCES ${SOURCES_WILDCARD})

find_package(Boost 1.55.0 REQUIRED COMPONENTS regex)
list(APPEND INCLUDED_HEADERS ${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

foreach(module ${INCLUDED_MODULE_HEADERS})
	list(APPEND INCLUDED_HEADERS ${UNKNOWN_ENGINE_SOURCE_DIR}/${module}/include)
endforeach(module)

if(INCLUDED_HEADERS)
        include_directories( ${INCLUDED_HEADERS} )
endif(INCLUDED_HEADERS)

if(LINKAGE)
    if(LINKAGE STREQUAL SHARED OR LINKAGE STREQUAL STATIC)
        add_library(${TARGET_NAME} ${LINKAGE} ${SOURCES})

	include(GenerateExportHeader)
	GENERATE_EXPORT_HEADER(${TARGET_NAME} EXPORT_FILE_NAME ${UNKNOWN_ENGINE_SOURCE_DIR}/SharedLibrariesExportHeaders/${TARGET_NAME}_export.h)
    elseif(LINKAGE STREQUAL INCLUDES_ONLY)
        add_custom_target(${TARGET_NAME} SOURCES ${SOURCES})
    endif(LINKAGE STREQUAL SHARED OR LINKAGE STREQUAL STATIC)
	
else(LINKAGE)
    add_executable(${TARGET_NAME} ${SOURCES})
endif(LINKAGE)

if(LINKED_LIBS)
	target_link_libraries(${TARGET_NAME} ${LINKED_LIBS} )
endif(LINKED_LIBS)

if(DEPENDS_ON_TARGETS)
	add_dependencies( ${TARGET_NAME} ${DEPENDS_ON_TARGETS} )
endif(DEPENDS_ON_TARGETS)

if(NOT LINKAGE)
    install(TARGETS ${TARGET_NAME} DESTINATION ${EXECUTABLE_DEPLOY_DIR})
else(NOT LINKAGE)
    if(LINKAGE STREQUAL STATIC)
        install(TARGETS ${TARGET_NAME} ARCHIVE DESTINATION ${STATIC_LIB_DEPLOY_DIR})
    elseif(LINKAGE STREQUAL SHARED)
        install(TARGETS ${TARGET_NAME} DESTINATION ${SHARED_LIB_DEPLOY_DIR})
    endif(LINKAGE STREQUAL STATIC)
endif(NOT LINKAGE)

# Deploy
if(DEPLOY_INCLUDES)
	if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/include)
		install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/${TARGET_NAME} DESTINATION ${INCLUDE_DEPLOY_DIR})
	endif(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/include)
endif(DEPLOY_INCLUDES)

if(DEPLOY_INCLUDES_PLAIN)
	if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/include)
		install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include DESTINATION ${INCLUDE_DEPLOY_DIR})
	endif(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/include)
endif(DEPLOY_INCLUDES_PLAIN)

# Precompiled headers
set(___PCH_INCLUDE___ ${UNKNOWN_ENGINE_SOURCE_DIR}/${TARGET_NAME}/stdafx.h)
set(___PCH_SOURCE___ ${UNKNOWN_ENGINE_SOURCE_DIR}/${TARGET_NAME}/stdafx.cpp)

if(NOT LINKAGE STREQUAL INCLUDES_ONLY)
    if(EXISTS ${___PCH_INCLUDE___} )
        if(EXISTS ${___PCH_SOURCE___} )
		include_directories( ${UNKNOWN_ENGINE_SOURCE_DIR}/Common )
		include_directories( ${UNKNOWN_ENGINE_SOURCE_DIR}/${TARGET_NAME} )
		include(${PCH_CMAKELISTS_FILE})
            if(COMPILER_SUPPORTS_PCH)
                add_precompiled_header(${TARGET_NAME} ${___PCH_INCLUDE___} ${___PCH_SOURCE___})
            endif(COMPILER_SUPPORTS_PCH)
        endif(EXISTS ${___PCH_SOURCE___} )
    endif(EXISTS ${___PCH_INCLUDE___} )
endif(NOT LINKAGE STREQUAL INCLUDES_ONLY)
