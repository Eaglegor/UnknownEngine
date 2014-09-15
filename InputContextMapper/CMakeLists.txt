set(TARGET_NAME InputContextMapper)
set(LINKAGE SHARED)

set(INCLUDED_MODULE_HEADERS InputContextMapper Plugins ComponentSystem Utils Engine UserInput Math)
set(LINKED_LIBS Engine ComponentSystem Plugins )
set(DEPENDS_ON_TARGETS ${LINKED_LIBS} )

include(${MODULE_TEMPLATE_CMAKELISTS_FILE})
