set(TARGET_NAME PhysXPlugin)
set(LINKAGE SHARED)

set(INCLUDED_MODULE_HEADERS PhysXPlugin Plugins Math ComponentSystem Utils Engine ResourceManager)
set(LINKED_LIBS Engine ComponentSystem Plugins ResourceManager )
set(DEPENDS_ON_TARGETS Engine ComponentSystem Plugins ResourceManager )

find_package(Eigen REQUIRED)
list(APPEND INCLUDED_HEADERS ${EIGEN_INCLUDE_DIR})

find_package(PhysX3 REQUIRED)
list( APPEND INCLUDED_HEADERS ${PhysX3_INCLUDE_DIRS})
list( APPEND LINKED_LIBS ${PhysX3_LIBRARIES})

include(${MODULE_TEMPLATE_CMAKELISTS_FILE})
