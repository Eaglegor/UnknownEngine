set(TARGET_NAME DummySubsystem)
set(LINKAGE SHARED)

set(INCLUDED_MODULE_HEADERS DummySubsystem Plugins ComponentSystem Utils Engine LogManager)
set(LINKED_LIBS Engine ComponentSystem Plugins LogManager )
set(DEPENDS_ON_TARGETS ${LINKED_LIBS} )

include(${MODULE_TEMPLATE_CMAKELISTS_FILE})
