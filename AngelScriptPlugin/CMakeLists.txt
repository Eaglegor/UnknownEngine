set(TARGET_NAME AngelScriptPlugin)
set(LINKAGE SHARED)

set(INCLUDED_MODULE_HEADERS AngelScriptPlugin Plugins ComponentSystem MessageSystem Utils Engine Math ResourceManager LogManager MessageSystem)
set(LINKED_LIBS Engine ComponentSystem Plugins LogManager MessageSystem)
set(DEPENDS_ON_TARGETS ${LINKED_LIBS} )

list(APPEND INCLUDED_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/add_on)
list(APPEND ADDITIONAL_SOURCE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/add_on)

find_package(AngelScript)
if(ANGELSCRIPT_FOUND)

	list( APPEND INCLUDED_HEADERS ${ANGELSCRIPT_INCLUDE_DIRS})
	list( APPEND LINKED_LIBS ${ANGELSCRIPT_LIBRARIES})

	include(${MODULE_TEMPLATE_CMAKELISTS_FILE})
endif()
