set(TARGET_NAME Application)

set(INCLUDED_MODULE_HEADERS Engine XmlSceneLoader SceneLoader )
set(LINKED_LIBS Engine XmlSceneLoader )
set(DEPENDS_ON_TARGETS ${LINKED_LIBS} )

include(${MODULE_TEMPLATE_CMAKELISTS_FILE})
