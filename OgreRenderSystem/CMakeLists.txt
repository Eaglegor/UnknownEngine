set(TARGET_NAME OgreRenderSystem)
set(LINKAGE SHARED)

set(INCLUDED_MODULE_HEADERS RenderSystem OgreRenderSystem Plugins ComponentSystem Utils Engine)
set(LINKED_LIBS Engine ComponentSystem Plugins gdi32 user32 )
set(DEPENDS_ON_TARGETS Engine ComponentSystem Plugins )

include(${MODULE_TEMPLATE_CMAKELISTS_FILE})
