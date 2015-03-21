cmake_minimum_required(VERSION 2.8.4)

project(UNKNOWN_ENGINE)

if(WIN32)
	set(Boost_USE_STATIC_LIBS ON)
endif(WIN32)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${UNKNOWN_ENGINE_SOURCE_DIR}/CMakeModules/)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${UNKNOWN_ENGINE_SOURCE_DIR}/CMakeModules/FindModules)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug)
endif()

set(EXECUTABLE_DEPLOY_DIR ${UNKNOWN_ENGINE_BINARY_DIR}/Output/${CMAKE_BUILD_TYPE}/bin)
set(STATIC_LIB_DEPLOY_DIR ${UNKNOWN_ENGINE_BINARY_DIR}/Output/${CMAKE_BUILD_TYPE}/lib)
set(SHARED_LIB_DEPLOY_DIR ${UNKNOWN_ENGINE_BINARY_DIR}/Output/${CMAKE_BUILD_TYPE}/bin)
set(INCLUDE_DEPLOY_DIR ${UNKNOWN_ENGINE_BINARY_DIR}/Output/${CMAKE_BUILD_TYPE}/include)

set(DEPLOY_INCLUDES FALSE)
set(DEPLOY_INCLUDES_PLAIN FALSE)

include(DetectCompiler)
include(CompilerFlags/${CMAKE_CXX_COMPILER_ID})

set(MODULE_TEMPLATE_CMAKELISTS_FILE CMakeModuleTemplate) 
set(PCH_CMAKELISTS_FILE PCHSupport)

set(
CROSS_PLATFORM_TARGETS

#Core
MessageSystem
ComponentSystem
Plugins
Engine
XmlSceneLoader
Math
Application
SceneLoader
Utils
ResourceManager
SimpleBehaviorPlugin
LogManager

#Subsystems
DummySubsystem

RenderSystem
OgreRenderSystem
AssimpMeshDataLoader

InputContextMapper
UserInput
SDLWindowManagerPlugin

PhysXPlugin

AngelScriptPlugin

Endoscopy
CEGuiPlugin

Media
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

message(STATUS "Building modules:")

foreach(build_module ${MODULES_TO_BUILD})
	message(STATUS " * ${build_module}")
endforeach(build_module)
