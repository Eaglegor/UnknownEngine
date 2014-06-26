set(TARGET_NAME Engine)
set(LINKAGE SHARED)

set(INCLUDED_MODULE_HEADERS Engine ComponentSystem Plugins SceneLoader RenderSystem Utils )
set(LINKED_LIBS ComponentSystem Plugins )
set(DEPENDS_ON_TARGETS ${LINKED_LIBS} )

include(${MODULE_TEMPLATE_CMAKELISTS_FILE})
