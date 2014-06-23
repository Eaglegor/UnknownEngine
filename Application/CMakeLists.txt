set(TARGET_NAME Application)

file(GLOB_RECURSE SOURCES "*.cpp" ".h")

set(INCLUDED_MODULE_HEADERS Deps Engine XmlSceneLoader SceneLoader )
set(LINKED_LIBS Engine XmlSceneLoader )
set(DEPENDS_ON_TARGETS ${LINKED_LIBS} )





foreach(module ${INCLUDED_MODULE_HEADERS})
	list(APPEND INCLUDED_HEADERS ${UNKNOWN_ENGINE_SOURCE_DIR}/${module}/include)
endforeach(module)

add_executable(${TARGET_NAME} ${SOURCES})

if(INCLUDED_HEADERS)
	include_directories( ${INCLUDED_HEADERS} )
endif(INCLUDED_HEADERS)

if(LINKED_LIBS)
	target_link_libraries(${TARGET_NAME} ${LINKED_LIBS} )
endif(LINKED_LIBS)

if(DEPENDS_ON_TARGETS)
	add_dependencies( ${TARGET_NAME} ${DEPENDS_ON_TARGETS} )
endif(DEPENDS_ON_TARGETS)
