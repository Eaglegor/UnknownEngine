set(TARGET_NAME OgreRenderSystem)
set(LINKAGE SHARED)

set(INCLUDED_MODULE_HEADERS RenderSystem OgreRenderSystem Plugins Math ComponentSystem Utils Engine ResourceManager)
set(LINKED_LIBS Engine ComponentSystem Plugins )
set(DEPENDS_ON_TARGETS Engine ComponentSystem Plugins )

find_package(Eigen REQUIRED)
list(APPEND INCLUDED_HEADERS ${EIGEN_INCLUDE_DIR})

find_package(OGRE REQUIRED)
list( APPEND INCLUDED_HEADERS ${OGRE_INCLUDE_DIRS})
list( APPEND LINKED_LIBS ${OGRE_LIBRARIES})
link_directories(${OGRE_LIBRARY_DIRS})

if(WIN32)
  configure_file(config/plugins.cfg.windows config/plugins.cfg)
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/config/plugins.cfg DESTINATION ${EXECUTABLE_DEPLOY_DIR})
  install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/config/OgreComponentsTestScene.xml DESTINATION ${EXECUTABLE_DEPLOY_DIR})
  install(FILES ${OGRE_BINARY_DIR}/OgreMain.dll ${OGRE_BINARY_DIR}/RenderSystem_GL.dll ${OGRE_BINARY_DIR}/Plugin_OctreeSceneManager.dll DESTINATION ${EXECUTABLE_DEPLOY_DIR} CONFIGURATIONS Release)
  install(FILES ${OGRE_BINARY_DIR}/Release/OgreMain.dll ${OGRE_BINARY_DIR}/release/RenderSystem_GL.dll ${OGRE_BINARY_DIR}/release/Plugin_OctreeSceneManager.dll DESTINATION ${EXECUTABLE_DEPLOY_DIR} CONFIGURATIONS Debug)
else()
  configure_file(config/plugins.cfg.linux config/plugins.cfg)
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/config/plugins.cfg DESTINATION ${EXECUTABLE_DEPLOY_DIR})
endif()

include(${MODULE_TEMPLATE_CMAKELISTS_FILE})
