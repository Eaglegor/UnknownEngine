set(TARGET_NAME XmlSceneLoader)
set(LINKAGE SHARED)

set(INCLUDED_MODULE_HEADERS XmlSceneLoader SceneLoader Plugins ComponentSystem Engine )
set(LINKED_LIBS Plugins ComponentSystem )
set(DEPENDS_ON_TARGETS ${LINKED_LIBS} )

list(APPEND LINKED_LIBS boost_regex-mgw48-mt-d-1_55)

include(${MODULE_TEMPLATE_CMAKELISTS_FILE})
