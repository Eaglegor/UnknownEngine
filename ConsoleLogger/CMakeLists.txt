set(TARGET_NAME ConsoleLogger)
set(LINKAGE SHARED)

set(INCLUDED_MODULE_HEADERS ConsoleLogger Plugins MessageSystem Utils Engine LogManager)
set(LINKED_LIBS Engine MessageSystem Plugins LogManager)
set(DEPENDS_ON_TARGETS ${LINKED_LIBS} )

include(${MODULE_TEMPLATE_CMAKELISTS_FILE})
