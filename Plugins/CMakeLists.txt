set(TARGET_NAME Plugins)
set(LINKAGE SHARED)

set(INCLUDED_MODULE_HEADERS Plugins ComponentSystem Engine Utils LogManager)
set(LINKED_LIBS ComponentSystem LogManager)
set(DEPENDS_ON_TARGETS ${LINKED_LIBS})

if(NOT WIN32)
  find_package(DL REQUIRED)
  if(DL_FOUND)
    list(APPEND INCLUDED_HEADERS ${DL_INCLUDE_DIR})
    list(APPEND LINKED_LIBS ${DL_LIBRARIES})
  endif(DL_FOUND)
endif(NOT WIN32)

include(${MODULE_TEMPLATE_CMAKELISTS_FILE})
