set(TARGET_NAME Application)

set(INCLUDED_MODULE_HEADERS ComponentSystem Engine XmlSceneLoader Utils ResourceManager SceneLoader Plugins Application )
set(LINKED_LIBS Engine XmlSceneLoader Plugins ResourceManager ComponentSystem )
set(DEPENDS_ON_TARGETS ${LINKED_LIBS} )

find_package(Boost 1.55.0 REQUIRED COMPONENTS program_options)
list(APPEND LINKED_LIBS ${Boost_LIBRARIES})
link_directories(${Boost_LIBRARY_DIRS})

include(${MODULE_TEMPLATE_CMAKELISTS_FILE})

if(NOT WIN32)
	install(
	FILES ${CMAKE_CURRENT_SOURCE_DIR}/scripts/run.sh 
	DESTINATION ${EXECUTABLE_DEPLOY_DIR} 
	PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE 
	)
endif()