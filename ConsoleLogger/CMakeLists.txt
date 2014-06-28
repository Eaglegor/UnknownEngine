set(TARGET_NAME ConsoleLogger)
set(LINKAGE SHARED)

set(INCLUDED_MODULE_HEADERS ConsoleLogger Plugins ComponentSystem Utils Engine)
set(LINKED_LIBS Engine ComponentSystem Plugins )
set(DEPENDS_ON_TARGETS ${LINKED_LIBS} )

include(${MODULE_TEMPLATE_CMAKELISTS_FILE})
