cmake_minimum_required(VERSION 2.8.4)

project(UNKNOWN_ENGINE)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${UNKNOWN_ENGINE_SOURCE_DIR}/CMakeModules/)

set(EXECUTABLE_DEPLOY_DIR ${UNKNOWN_ENGINE_BINARY_DIR}/Output/bin)
set(STATIC_LIB_DEPLOY_DIR ${UNKNOWN_ENGINE_BINARY_DIR}/Output/lib)
set(SHARED_LIB_DEPLOY_DIR ${UNKNOWN_ENGINE_BINARY_DIR}/Output/bin)
set(INCLUDE_DEPLOY_DIR ${UNKNOWN_ENGINE_BINARY_DIR}/Output)

set(DEPLOY_INCLUDES FALSE)
set(DEPLOY_INCLUDES_PLAIN FALSE)

set(CMAKE_BUILD_TYPE Debug)

include(${UNKNOWN_ENGINE_SOURCE_DIR}/CMakeModules/DetectCompiler.cmake)

set(MODULE_TEMPLATE_CMAKELISTS_FILE CMakeModuleTemplate) 
set(PCH_CMAKELISTS_FILE PCHSupport)

if(WIN32 OR CYGWIN)
  if(MINGW)
    list(APPEND CMAKE_CXX_FLAGS " -std=c++11 -pipe -g3 -O0 -Wpedantic -U__STRICT_ANSI__ ")
  elseif(MSVC)
    list(APPEND CMAKE_CXX_FLAGS " /Zi /Od ")
  elseif(CYGWIN)
    list(APPEND CMAKE_CXX_FLAGS " -std=c++11 -pipe -g3 -O0 -Wpedantic ")
  endif(MINGW)
else(WIN32 OR CYGWIN)
  list(APPEND CMAKE_CXX_FLAGS " -std=c++11 -pipe -g3 -O0 ")
endif(WIN32 OR CYGWIN)

set(
CROSS_PLATFORM_TARGETS

#Core
ComponentSystem
Plugins
Engine
XmlSceneLoader
Math
Application
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


