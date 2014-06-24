set(TARGET_NAME RenderSystem)
set(LINKAGE STATIC)

set(INCLUDED_MODULE_HEADERS RenderSystem Engine Plugins Utils ComponentSystem Deps )
set(LINKED_LIBS  )
set(DEPENDS_ON_TARGETS ${LINKED_LIBS} )

include(${MODULE_TEMPLATE_CMAKELISTS_FILE})
