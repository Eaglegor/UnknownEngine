set(TARGET_NAME Plugins)
set(LINKAGE SHARED)

file(GLOB_RECURSE SOURCES "*.cpp" "*.h")

set(INCLUDED_MODULE_HEADERS Plugins ComponentSystem Engine Deps)
set(LINKED_LIBS ComponentSystem)
set(DEPENDS_ON_TARGETS ComponentSystem)





foreach(module ${INCLUDED_MODULE_HEADERS})
	list(APPEND INCLUDED_HEADERS ${UNKNOWN_ENGINE_SOURCE_DIR}/${module}/include)
endforeach(module)

add_library(${TARGET_NAME} ${LINKAGE} ${SOURCES})

if(INCLUDED_HEADERS)
	include_directories( ${INCLUDED_HEADERS} )
endif(INCLUDED_HEADERS)

if(LINKED_LIBS)
	target_link_libraries(${TARGET_NAME} ${LINKED_LIBS} )
endif(LINKED_LIBS)

if(DEPENDS_ON_TARGETS)
	add_dependencies( ${TARGET_NAME} ${DEPENDS_ON_TARGETS} )
endif(DEPENDS_ON_TARGETS)
