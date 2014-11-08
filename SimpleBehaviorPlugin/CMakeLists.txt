set(TARGET_NAME SimpleBehaviorPlugin)
set(LINKAGE SHARED)

set(INCLUDED_MODULE_HEADERS SimpleBehaviorPlugin InputContextMapper Plugins ComponentSystem Utils Engine Math RenderSystem)
set(LINKED_LIBS Engine ComponentSystem Plugins )
set(DEPENDS_ON_TARGETS ${LINKED_LIBS} )

find_package(Eigen REQUIRED)
list(APPEND INCLUDED_HEADERS ${EIGEN_INCLUDE_DIR})

include(${MODULE_TEMPLATE_CMAKELISTS_FILE})
