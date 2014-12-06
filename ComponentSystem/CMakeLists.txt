set(TARGET_NAME ComponentSystem)
set(LINKAGE SHARED)

set(INCLUDED_MODULE_HEADERS Engine ComponentSystem MessageSystem Utils LogManager)
set(LINKED_LIBS MessageSystem LogManager)
set(DEPENDS_ON_TARGETS ${LINKED_LIBS} )

include(${MODULE_TEMPLATE_CMAKELISTS_FILE})