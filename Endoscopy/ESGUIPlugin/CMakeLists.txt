set(TARGET_NAME ESGUIPlugin)
set(LINKAGE SHARED)

set(INCLUDED_MODULE_HEADERS Endoscopy/ESGUIPlugin MessageSystem CEGuiPlugin Plugins Utils Math Engine LogManager ComponentSystem)
set(LINKED_LIBS Engine Plugins LogManager ComponentSystem CEGuiPlugin )
set(DEPENDS_ON_TARGETS ${LINKED_LIBS} )

find_package(CEGUI COMPONENTS OgreRenderer)

if(CEGUI_FOUND)
	list(APPEND INCLUDED_HEADERS ${CEGUI_INCLUDE_DIRS})
	list(APPEND LINKED_LIBS ${CEGUI_LIBRARIES})
	list(APPEND INCLUDED_HEADERS ${CEGUI_OgreRenderer_INCLUDE_DIRS})
	list(APPEND LINKED_LIBS ${CEGUI_OgreRenderer_LIBRARIES})
	find_package(OGRE)
	link_directories(${OGRE_LIBRARY_DIRS})
endif()

set(___PCH_INCLUDE___ ${CMAKE_CURRENT_SOURCE_DIR}/stdafx.h)
set(___PCH_SOURCE___ ${CMAKE_CURRENT_SOURCE_DIR}/stdafx.cpp)
list(APPEND INCLUDED_HEADERS ${CMAKE_CURRENT_SOURCE_DIR})

include(${MODULE_TEMPLATE_CMAKELISTS_FILE})