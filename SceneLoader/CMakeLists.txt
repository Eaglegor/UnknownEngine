set(TARGET_NAME SceneLoader)
set(LINKAGE INCLUDES_ONLY)

set(INCLUDED_MODULE_HEADERS Engine )
set(LINKED_LIBS  )
set(DEPENDS_ON_TARGETS ${LINKED_LIBS} )

include(${MODULE_TEMPLATE_CMAKELISTS_FILE})
