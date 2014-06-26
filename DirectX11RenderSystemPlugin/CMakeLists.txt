set(TARGET_NAME DirectX11RenderSystemPlugin)
set(LINKAGE SHARED)

set(INCLUDED_MODULE_HEADERS DirectX11RenderSystemPlugin DirectX11RenderSystem Plugins RenderSystem ComponentSystem Utils Engine)
set(LINKED_LIBS Engine RenderSystem ComponentSystem Plugins DirectX11RenderSystem gdi32 user32 )
set(DEPENDS_ON_TARGETS Engine RenderSystem ComponentSystem Plugins DirectX11RenderSystem )

include(${MODULE_TEMPLATE_CMAKELISTS_FILE})
