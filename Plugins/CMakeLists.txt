set(TARGET_NAME Plugins)
set(LINKAGE SHARED)

set(INCLUDED_MODULE_HEADERS Plugins ComponentSystem Engine)
set(LINKED_LIBS ComponentSystem)
set(DEPENDS_ON_TARGETS ComponentSystem)

include(${MODULE_TEMPLATE_CMAKELISTS_FILE})
