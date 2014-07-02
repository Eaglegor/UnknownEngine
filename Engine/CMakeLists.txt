set(TARGET_NAME Engine)
set(LINKAGE SHARED)

set(INCLUDED_MODULE_HEADERS Engine ComponentSystem Plugins SceneLoader RenderSystem Utils ResourceManager )
set(LINKED_LIBS ComponentSystem Plugins ResourceManager )
set(DEPENDS_ON_TARGETS ${LINKED_LIBS} )

include(${MODULE_TEMPLATE_CMAKELISTS_FILE})
