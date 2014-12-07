set(TARGET_NAME DummySubsystem)
set(LINKAGE SHARED)

set(INCLUDED_MODULE_HEADERS DummySubsystem Plugins MessageSystem Utils Engine LogManager)
set(LINKED_LIBS Engine MessageSystem Plugins LogManager )
set(DEPENDS_ON_TARGETS ${LINKED_LIBS} )

include(${MODULE_TEMPLATE_CMAKELISTS_FILE})
