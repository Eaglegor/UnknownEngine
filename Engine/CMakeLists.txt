set(TARGET_NAME Engine)
set(LINKAGE SHARED)

set(INCLUDED_MODULE_HEADERS Engine ComponentSystem Plugins SceneLoader Math RenderSystem Utils ResourceManager LogManager )
set(LINKED_LIBS ComponentSystem Plugins ResourceManager LogManager )
set(DEPENDS_ON_TARGETS ${LINKED_LIBS} )

find_package(Eigen REQUIRED)
list(APPEND INCLUDED_HEADERS ${EIGEN_INCLUDE_DIR})

include(${MODULE_TEMPLATE_CMAKELISTS_FILE})
