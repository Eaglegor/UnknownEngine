set(TARGET_NAME Application)

set(INCLUDED_MODULE_HEADERS Application Utils Engine ComponentSystem MessageSystem LogManager ResourceManager Math XmlSceneLoader SceneLoader Plugins )
set(LINKED_LIBS Engine LogManager ComponentSystem ResourceManager XmlSceneLoader )
set(DEPENDS_ON_TARGETS ${LINKED_LIBS} )

find_package(Boost 1.55.0 REQUIRED COMPONENTS program_options)
list(APPEND LINKED_LIBS ${Boost_LIBRARIES})
link_directories(${Boost_LIBRARY_DIRS})

include(${MODULE_TEMPLATE_CMAKELISTS_FILE})
