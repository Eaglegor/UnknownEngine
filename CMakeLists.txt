cmake_minimum_required(VERSION 2.8)

project(UNKNOWN_ENGINE)

set(DIRECTX_INCLUDE_DIR ${DIRECTX_HOME}/Include)
set(EXECUTABLE_DEPLOY_DIR ${UNKNOWN_ENGINE_BINARY_DIR}/Output/bin)
set(STATIC_LIB_DEPLOY_DIR ${UNKNOWN_ENGINE_BINARY_DIR}/Output/lib)
set(SHARED_LIB_DEPLOY_DIR ${UNKNOWN_ENGINE_BINARY_DIR}/Output/bin)
set(INCLUDE_DEPLOY_DIR ${UNKNOWN_ENGINE_BINARY_DIR}/Output)

set(DEPLOY_INCLUDES FALSE)

list(APPEND CMAKE_CXX_FLAGS " -std=c++11 -g3 -O0 ")

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

