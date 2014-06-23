set(TARGET_NAME DirectX11RenderSystemPlugin)
set(LINKAGE SHARED)

file(GLOB_RECURSE SOURCES "*.cpp")

set(INCLUDED_MODULE_HEADERS DirectX11RenderSystemPlugin DirectX11RenderSystem Plugins RenderSystem ComponentSystem Utils Engine Deps)
set(LINKED_LIBS Engine RenderSystem ComponentSystem Plugins DirectX11RenderSystem gdi32 user32 )
set(DEPENDS_ON_TARGETS Engine RenderSystem ComponentSystem Plugins DirectX11RenderSystem )





foreach(module ${INCLUDED_MODULE_HEADERS})
	list(APPEND INCLUDED_HEADERS ${UNKNOWN_ENGINE_SOURCE_DIR}/${module}/include)
endforeach(module)

add_library(${TARGET_NAME} ${LINKAGE} ${SOURCES})

if(INCLUDED_HEADERS)
	include_directories( ${INCLUDED_HEADERS} )
endif(INCLUDED_HEADERS)

if(LINKED_LIBS)
	target_link_libraries(${TARGET_NAME} ${LINKED_LIBS} )
endif(LINKED_LIBS)

if(DEPENDS_ON_TARGETS)
	add_dependencies( ${TARGET_NAME} ${DEPENDS_ON_TARGETS} )
endif(DEPENDS_ON_TARGETS)
