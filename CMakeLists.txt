cmake_minimum_required(VERSION 2.8)

project(UNKNOWN_ENGINE)

set(DIRECTX_INCLUDE_DIR $ENV{DXSDK_DIR}/Include)
set(EXECUTABLE_DEPLOY_DIR ${UNKNOWN_ENGINE_BINARY_DIR}/Output/bin)
set(STATIC_LIB_DEPLOY_DIR ${UNKNOWN_ENGINE_BINARY_DIR}/Output/lib)
set(SHARED_LIB_DEPLOY_DIR ${UNKNOWN_ENGINE_BINARY_DIR}/Output/bin)
set(INCLUDE_DEPLOY_DIR ${UNKNOWN_ENGINE_BINARY_DIR}/Output)

set(DEPLOY_INCLUDES FALSE)
set(DEPLOY_INCLUDES_PLAIN FALSE)

set(CMAKE_BUILD_TYPE Debug)

set(MODULE_TEMPLATE_CMAKELISTS_FILE ${UNKNOWN_ENGINE_SOURCE_DIR}/CMakeModuleTemplate.cmake)
set(PCH_CMAKELISTS_FILE ${UNKNOWN_ENGINE_SOURCE_DIR}/PCHSupport.cmake)

if(WIN32)
  if(MINGW)
    list(APPEND CMAKE_CXX_FLAGS " -std=c++11 -pipe -g3 -O0 -Wpedantic ")
  elseif(MSVC)
    list(APPEND CMAKE_CXX_FLAGS " /Zi /Od ")
  endif(MINGW)
else(WIN32)
  list(APPEND CMAKE_CXX_FLAGS " -std=c++11 -pipe -g3 -O0 ")
endif(WIN32)


set(
CROSS_PLATFORM_TARGETS

#Core
ComponentSystem
Plugins
Engine
XmlSceneLoader
Math
Application
Deps
SceneLoader
Utils
ResourceManager

#Subsystems
DummySubsystem
ConsoleLogger

RenderSystem
OgreRenderSystem
)

set(
WIN32_ONLY_TARGETS

)

list(APPEND ALL_TARGETS_LIST ${CROSS_PLATFORM_TARGETS})

if(WIN32)
    list(APPEND ALL_TARGETS_LIST ${WIN32_ONLY_TARGETS})
endif(WIN32)

foreach(targets_list ${ALL_TARGETS_LIST})
	foreach(target ${targets_list})
		add_subdirectory(${target})
	endforeach(target)
endforeach(targets_list)


