set(TARGET_NAME SDLUserInputPlugin)
set(LINKAGE SHARED)

set(INCLUDED_MODULE_HEADERS SDLUserInputPlugin UserInput Plugins ComponentSystem Utils Engine UserInput)
set(LINKED_LIBS Engine ComponentSystem Plugins )
set(DEPENDS_ON_TARGETS ${LINKED_LIBS} )

find_package(SDL)

if(SDL_FOUND)

	list( APPEND INCLUDED_HEADERS ${SDL_INCLUDE_DIR})
	list( APPEND LINKED_LIBS ${SDL_LIBRARY})

	include(${MODULE_TEMPLATE_CMAKELISTS_FILE})
  
endif(SDL_FOUND)