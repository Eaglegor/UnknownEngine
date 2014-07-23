set(TARGET_NAME OgreRenderSystem)
set(LINKAGE SHARED)

set(INCLUDED_MODULE_HEADERS RenderSystem OgreRenderSystem Plugins Math ComponentSystem Utils Engine ResourceManager)
set(LINKED_LIBS Engine ComponentSystem Plugins )
set(DEPENDS_ON_TARGETS Engine ComponentSystem Plugins )

list( APPEND INCLUDED_HEADERS ${UNKNOWN_ENGINE_SOURCE_DIR}/Deps/include/OGRE )

if(WIN32)
    if(MINGW)
        list(APPEND LINKED_LIBS OgreMain )
        list(APPEND LINKED_LIBS OgrePaging )
        list(APPEND LINKED_LIBS OgreProperty )
        list(APPEND LINKED_LIBS RenderSystem_Direct3D9 )
    elseif(MSVC)
        list(APPEND LINKED_LIBS OgreMain)
    endif(MINGW)
else(WIN32)
    list(APPEND LINKED_LIBS OgreMain)
endif(WIN32)

include(${MODULE_TEMPLATE_CMAKELISTS_FILE})
