cmake_minimum_required(VERSION 3.0)

project(UNKNOWNENGINE_DEPS)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${UNKNOWN_ENGINE_SOURCE_DIR}/CMakeModules/)

#Scripts
add_subdirectory(angelscript)

#Common
add_subdirectory(boost)

#Assets
add_subdirectory(assimp)

#GUI
add_subdirectory(cegui)
add_subdirectory(sdl)

#Math
add_subdirectory(eigen)

#Graphics
add_subdirectory(ogre)

#Physics
add_subdirectory(physx)
