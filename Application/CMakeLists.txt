set(TARGET_NAME Application)

set(INCLUDED_MODULE_HEADERS ComponentSystem Engine XmlSceneLoader SceneLoader Plugins )
set(LINKED_LIBS Engine XmlSceneLoader Plugins )
set(DEPENDS_ON_TARGETS ${LINKED_LIBS} )

find_package(Boost 1.55.0 REQUIRED COMPONENTS program_options)
list(APPEND LINKED_LIBS ${Boost_LIBRARIES})
link_directories(${Boost_LIBRARY_DIRS})

include(${MODULE_TEMPLATE_CMAKELISTS_FILE})
