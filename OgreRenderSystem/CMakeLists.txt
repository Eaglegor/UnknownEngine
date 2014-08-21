set(TARGET_NAME OgreRenderSystem)
set(LINKAGE SHARED)

set(INCLUDED_MODULE_HEADERS RenderSystem OgreRenderSystem Plugins Math ComponentSystem Utils Engine ResourceManager)
set(LINKED_LIBS Engine ComponentSystem Plugins ResourceManager )
set(DEPENDS_ON_TARGETS Engine ComponentSystem Plugins ResourceManager )

find_package(Eigen REQUIRED)
list(APPEND INCLUDED_HEADERS ${EIGEN_INCLUDE_DIR})

find_package(OGRE REQUIRED)
list( APPEND INCLUDED_HEADERS ${OGRE_INCLUDE_DIRS})
list( APPEND LINKED_LIBS ${OGRE_LIBRARIES})
link_directories(${OGRE_LIBRARY_DIRS})

if(OGRE_FOUND)

  if(WIN32)
	set(OGRE_LIB_SUFFIX _d)
    configure_file(config/plugins.cfg.windows config/plugins.cfg)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/config/plugins.cfg DESTINATION ${EXECUTABLE_DEPLOY_DIR})
    install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/config/OgreComponentsTestScene.xml DESTINATION ${EXECUTABLE_DEPLOY_DIR})
    install(FILES ${OGRE_BINARY_DIR}/OgreMain.dll ${OGRE_BINARY_DIR}/RenderSystem_GL.dll ${OGRE_BINARY_DIR}/Plugin_OctreeSceneManager.dll DESTINATION ${EXECUTABLE_DEPLOY_DIR} CONFIGURATIONS Release)
    install(FILES ${OGRE_BINARY_DIR}/OgreMain_d.dll ${OGRE_BINARY_DIR}/RenderSystem_GL_d.dll ${OGRE_BINARY_DIR}/Plugin_OctreeSceneManager_d.dll DESTINATION ${EXECUTABLE_DEPLOY_DIR} CONFIGURATIONS Debug)
  else(WIN32)
    configure_file(config/plugins.cfg.linux config/plugins.cfg)
    install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/config/OgreComponentsTestScene.xml DESTINATION ${EXECUTABLE_DEPLOY_DIR})
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/config/plugins.cfg DESTINATION ${EXECUTABLE_DEPLOY_DIR})
  endif(WIN32)

  find_package(TBB)
  if(TBB_FOUND)
	list(APPEND INCLUDED_HEADERS ${TBB_INCLUDE_DIRS})
	list(APPEND LINKED_LIBS ${TBB_LIBRARIES})
	link_directories(${TBB_LIBRARY_DIRS})

    find_package(Boost 1.55.0 REQUIRED COMPONENTS system thread)
    list(APPEND LINKED_LIBS ${Boost_LIBRARIES})
    link_directories(${Boost_LIBRARY_DIRS})
	
	list(APPEND INCLUDED_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/mt/TBB/include)
	file(GLOB_RECURSE ADDITIONAL_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/mt/TBB/src "*.cpp" "*.h")
	list(APPEND SOURCES ${ADDITIONAL_SOURCES})
  else()
	list(APPEND INCLUDED_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/mt/SingleThread/include)
	file(GLOB_RECURSE ADDITIONAL_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/mt/SingleThread/src "*.cpp" "*.h")
	list(APPEND SOURCES ${ADDITIONAL_SOURCES})
  endif()
  
  include(${MODULE_TEMPLATE_CMAKELISTS_FILE})
  
endif(OGRE_FOUND)

