set(TARGET_NAME OgreRenderSystem)
set(LINKAGE SHARED)

set(INCLUDED_MODULE_HEADERS RenderSystem OgreRenderSystem Plugins Math ComponentSystem MessageSystem Utils Engine ResourceManager LogManager)
set(LINKED_LIBS Engine ComponentSystem Plugins ResourceManager LogManager MessageSystem )
set(DEPENDS_ON_TARGETS ${LINKED_LIBS} )

find_package(Eigen REQUIRED)
list(APPEND INCLUDED_HEADERS ${EIGEN_INCLUDE_DIR})

find_package(OGRE)
list( APPEND INCLUDED_HEADERS ${OGRE_INCLUDE_DIRS})
list( APPEND LINKED_LIBS ${OGRE_LIBRARIES})
link_directories(${OGRE_LIBRARY_DIRS})

if(OGRE_FOUND)

  install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/config/OgreComponentsTestScene.xml DESTINATION ${EXECUTABLE_DEPLOY_DIR})
  install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/config/TestScene.xml DESTINATION ${EXECUTABLE_DEPLOY_DIR})
  install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/config/StressTestScene.xml DESTINATION ${EXECUTABLE_DEPLOY_DIR})
  install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/config/media DESTINATION ${EXECUTABLE_DEPLOY_DIR})
  install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/config/resources.cfg DESTINATION ${EXECUTABLE_DEPLOY_DIR})

  if(WIN32)
	set(OGRE_LIB_SUFFIX _d)
    configure_file(config/plugins.cfg.windows config/plugins.cfg)
    install(FILES ${OGRE_BINARY_DIR}/OgreMain.dll ${OGRE_BINARY_DIR}/RenderSystem_GL.dll ${OGRE_BINARY_DIR}/Plugin_OctreeSceneManager.dll DESTINATION ${EXECUTABLE_DEPLOY_DIR} CONFIGURATIONS Release)
    install(FILES ${OGRE_BINARY_DIR}/OgreMain_d.dll ${OGRE_BINARY_DIR}/RenderSystem_GL_d.dll ${OGRE_BINARY_DIR}/Plugin_OctreeSceneManager_d.dll DESTINATION ${EXECUTABLE_DEPLOY_DIR} CONFIGURATIONS Debug)
  else(WIN32)
    configure_file(config/plugins.cfg.linux config/plugins.cfg)
  endif(WIN32)

  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/config/plugins.cfg DESTINATION ${EXECUTABLE_DEPLOY_DIR})
 
  find_package(TBB)
  
	if(TBB_FOUND AND NOT DISABLE_TBB)
		message(STATUS "Intel Thread Building Blocks found")
		add_definitions(-DOGRE_RS_WITH_TBB)
		list(APPEND INCLUDED_HEADERS ${TBB_INCLUDE_DIRS})
		list(APPEND LINKED_LIBS ${TBB_LIBRARIES})
		link_directories(${TBB_LIBRARY_DIRS})
	endif()
 
  include(${MODULE_TEMPLATE_CMAKELISTS_FILE})
  
endif(OGRE_FOUND)

