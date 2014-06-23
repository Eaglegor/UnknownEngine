cmake_minimum_required(VERSION 2.8)

project(UNKNOWN_ENGINE)

set(DIRECTX_INCLUDE_DIR "C:\\Program Files (x86)\\Microsoft DirectX SDK (June 2010)\\Include")

set(
SHARED_LIBRARIES_LIST

ComponentSystem
Plugins
Engine
DirectX11RenderSystemPlugin
XmlSceneLoader
)

set(
STATIC_LIBRARIES_LIST

RenderSystem
DirectX11RenderSystem
Math
)

set(
EXECUTABLES_LIST

Application
)

set(
PURE_INCLUDES_LIST

Deps
SceneLoader
Utils
)

set(
ALL_TARGETS_LIST

${PURE_INCLUDES_LIST}
${STATIC_LIBRARIES_LIST}
${SHARED_LIBRARIES_LIST}
${EXECUTABLES_LIST}
)

foreach(targets_list ${ALL_TARGETS_LIST})
	foreach(target ${targets_list})
		add_subdirectory(${target})
	endforeach(target)
endforeach(targets_list)