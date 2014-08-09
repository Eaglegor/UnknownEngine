set(TARGET_NAME AssimpMeshDataLoader)
set(LINKAGE SHARED)

set(INCLUDED_MODULE_HEADERS AssimpMeshDataLoader ComponentSystem Math Plugins ResourceManager Utils Engine)
set(LINKED_LIBS Engine ComponentSystem Plugins )
set(DEPENDS_ON_TARGETS ${LINKED_LIBS} )

find_package(Eigen REQUIRED)
list(APPEND INCLUDED_HEADERS ${EIGEN_INCLUDE_DIR})

find_package(Assimp REQUIRED)
list( APPEND INCLUDED_HEADERS ${assimp_INCLUDE_DIRS})
list( APPEND LINKED_LIBS ${assimp_LIBRARIES})
link_directories(${ASSIMP_LIBRARY_DIRS})

if(assimp_FOUND)
	include(${MODULE_TEMPLATE_CMAKELISTS_FILE})
endif()
