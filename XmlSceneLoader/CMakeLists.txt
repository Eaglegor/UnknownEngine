set(TARGET_NAME XmlSceneLoader)
set(LINKAGE SHARED)

file(GLOB_RECURSE SOURCES "*.cpp")

set(INCLUDED_MODULE_HEADERS XmlSceneLoader SceneLoader Deps Plugins ComponentSystem Engine )
set(LINKED_LIBS )
set(DEPENDS_ON_TARGETS ${LINKED_LIBS} )





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
