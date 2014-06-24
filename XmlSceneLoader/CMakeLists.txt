set(TARGET_NAME XmlSceneLoader)
set(LINKAGE SHARED)

set(INCLUDED_MODULE_HEADERS XmlSceneLoader SceneLoader Deps Plugins ComponentSystem Engine )
set(LINKED_LIBS boost_regex-mgw48-mt-d-1_55 )
set(DEPENDS_ON_TARGETS ${LINKED_LIBS} )

include(${MODULE_TEMPLATE_CMAKELISTS_FILE})
