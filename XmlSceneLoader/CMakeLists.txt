set(TARGET_NAME XmlSceneLoader)
set(LINKAGE SHARED)

set(INCLUDED_MODULE_HEADERS XmlSceneLoader SceneLoader Plugins ResourceManager ComponentSystem Engine Utils )
set(LINKED_LIBS Plugins ComponentSystem )
set(DEPENDS_ON_TARGETS ${LINKED_LIBS} )

find_package(Boost 1.55.0 REQUIRED COMPONENTS regex)
list(APPEND LINKED_LIBS ${Boost_LIBRARIES})
link_directories(${Boost_LIBRARY_DIRS})

include(${MODULE_TEMPLATE_CMAKELISTS_FILE})
