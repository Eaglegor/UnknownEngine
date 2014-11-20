set(TARGET_NAME AngelScriptPlugin)
set(LINKAGE SHARED)

set(INCLUDED_MODULE_HEADERS AngelScriptPlugin Plugins ComponentSystem Utils Engine)
set(LINKED_LIBS Engine ComponentSystem Plugins )
set(DEPENDS_ON_TARGETS ${LINKED_LIBS} )

find_package(AngelScript)
if(ANGELSCRIPT_FOUND)

	list( APPEND INCLUDED_HEADERS ${ANGELSCRIPT_INCLUDE_DIRS})
	list( APPEND LINKED_LIBS ${ANGELSCRIPT_LIBRARIES})

	include(${MODULE_TEMPLATE_CMAKELISTS_FILE})
endif()
