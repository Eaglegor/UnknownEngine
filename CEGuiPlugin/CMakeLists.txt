set(TARGET_NAME CEGuiPlugin)
set(LINKAGE SHARED)

set(INCLUDED_MODULE_HEADERS CEGuiPlugin Plugins MessageSystem Utils Engine LogManager UserInput OgreRenderSystem ComponentSystem)
set(LINKED_LIBS Engine MessageSystem Plugins LogManager ComponentSystem )
set(DEPENDS_ON_TARGETS ${LINKED_LIBS} )

find_package(CEGUI COMPONENTS OgreRenderer)

if(CEGUI_FOUND)
	list(APPEND INCLUDED_HEADERS ${CEGUI_INCLUDE_DIRS})
	list(APPEND LINKED_LIBS ${CEGUI_LIBRARIES})
	list(APPEND INCLUDED_HEADERS ${CEGUI_OgreRenderer_INCLUDE_DIRS})
	list(APPEND LINKED_LIBS ${CEGUI_OgreRenderer_LIBRARIES})
endif()


find_package(OGRE)
if(OGRE_FOUND)
	list( APPEND INCLUDED_HEADERS ${OGRE_INCLUDE_DIRS})
	list( APPEND LINKED_LIBS ${OGRE_LIBRARIES})
	link_directories(${OGRE_LIBRARY_DIRS})
endif()

if(CEGUI_FOUND)
	include(${MODULE_TEMPLATE_CMAKELISTS_FILE})
endif()