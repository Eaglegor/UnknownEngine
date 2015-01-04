set(TARGET_NAME ESInstrumentHardwarePlugin)
set(LINKAGE SHARED)

set(INCLUDED_MODULE_HEADERS Endoscopy/ESInstrumentHardwarePlugin Plugins MessageSystem Utils Math Engine LogManager InputContextMapper ComponentSystem)
set(LINKED_LIBS Engine MessageSystem Plugins LogManager ComponentSystem )
set(DEPENDS_ON_TARGETS ${LINKED_LIBS} )

set(___PCH_INCLUDE___ ${CMAKE_CURRENT_SOURCE_DIR}/stdafx.h)
set(___PCH_SOURCE___ ${CMAKE_CURRENT_SOURCE_DIR}/stdafx.cpp)
list(APPEND INCLUDED_HEADERS ${CMAKE_CURRENT_SOURCE_DIR})

include(${MODULE_TEMPLATE_CMAKELISTS_FILE})
