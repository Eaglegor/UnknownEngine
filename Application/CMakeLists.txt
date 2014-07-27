set(TARGET_NAME Application)

set(INCLUDED_MODULE_HEADERS ComponentSystem Engine XmlSceneLoader SceneLoader Plugins )
set(LINKED_LIBS Engine XmlSceneLoader Plugins )
set(DEPENDS_ON_TARGETS ${LINKED_LIBS} )

include(${MODULE_TEMPLATE_CMAKELISTS_FILE})
