set(TARGET_NAME SDLWindowManagerPlugin)
set(LINKAGE SHARED)

set(INCLUDED_MODULE_HEADERS SDLWindowManagerPlugin UserInput Plugins ComponentSystem Utils Engine UserInput RenderSystem)
set(LINKED_LIBS Engine ComponentSystem Plugins )
set(DEPENDS_ON_TARGETS ${LINKED_LIBS} )

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 sdl2)

if(NOT SDL2_FOUND)
    find_package(SDL2)
endif()

if(SDL2_FOUND)

	list( APPEND INCLUDED_HEADERS ${SDL2_INCLUDE_DIRS})
	list( APPEND LINKED_LIBS ${SDL2_LIBRARIES})

	include(${MODULE_TEMPLATE_CMAKELISTS_FILE})
  
endif(SDL2_FOUND)