set(TARGET_NAME SimpleBehaviorPlugin)
set(LINKAGE SHARED)

set(INCLUDED_MODULE_HEADERS SimpleBehaviorPlugin InputContextMapper Plugins ComponentSystem MessageSystem Utils Engine Math RenderSystem LogManager)
set(LINKED_LIBS Engine ComponentSystem Plugins LogManager MessageSystem )
set(DEPENDS_ON_TARGETS ${LINKED_LIBS} )

find_package(Eigen REQUIRED)
list(APPEND INCLUDED_HEADERS ${EIGEN_INCLUDE_DIR})

include(${MODULE_TEMPLATE_CMAKELISTS_FILE})
