set(TARGET_NAME DummySubsystem)
set(LINKAGE SHARED)

set(INCLUDED_MODULE_HEADERS DummySubsystem Plugins ComponentSystem Utils Engine)
set(LINKED_LIBS Engine ComponentSystem Plugins )
set(DEPENDS_ON_TARGETS ${LINKED_LIBS} )

include(${MODULE_TEMPLATE_CMAKELISTS_FILE})
