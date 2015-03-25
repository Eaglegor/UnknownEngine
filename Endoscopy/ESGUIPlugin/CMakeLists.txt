set(TARGET_NAME ESGUIPlugin)
set(LINKAGE SHARED)

set(INCLUDED_MODULE_HEADERS Endoscopy/ESGUIPlugin CEGuiPlugin Plugins Utils Math Engine LogManager ComponentSystem)
set(LINKED_LIBS Engine Plugins LogManager ComponentSystem )
set(DEPENDS_ON_TARGETS ${LINKED_LIBS} )

set(___PCH_INCLUDE___ ${CMAKE_CURRENT_SOURCE_DIR}/stdafx.h)
set(___PCH_SOURCE___ ${CMAKE_CURRENT_SOURCE_DIR}/stdafx.cpp)
list(APPEND INCLUDED_HEADERS ${CMAKE_CURRENT_SOURCE_DIR})

include(${MODULE_TEMPLATE_CMAKELISTS_FILE})