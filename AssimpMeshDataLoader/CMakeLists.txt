set(TARGET_NAME AssimpMeshDataLoader)
set(LINKAGE SHARED)

set(INCLUDED_MODULE_HEADERS AssimpMeshDataLoader ComponentSystem Math Plugins ResourceManager Utils Engine LogManager)
set(LINKED_LIBS Engine ComponentSystem Plugins ResourceManager LogManager )
set(DEPENDS_ON_TARGETS ${LINKED_LIBS} )

find_package(Eigen REQUIRED)
list(APPEND INCLUDED_HEADERS ${EIGEN_INCLUDE_DIR})

find_package(Assimp)

if(Assimp_FOUND)

	list( APPEND INCLUDED_HEADERS ${Assimp_INCLUDE_DIRS})
	list( APPEND LINKED_LIBS ${Assimp_LIBRARIES})

	if(WIN32)
		install(FILES ${Assimp_SHARED_BINARIES} DESTINATION ${EXECUTABLE_DEPLOY_DIR})
	endif(WIN32)

	include(${MODULE_TEMPLATE_CMAKELISTS_FILE})
endif()
