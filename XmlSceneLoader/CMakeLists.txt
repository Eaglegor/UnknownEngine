set(TARGET_NAME XmlSceneLoader)
set(LINKAGE SHARED)

set(INCLUDED_MODULE_HEADERS XmlSceneLoader SceneLoader Plugins ComponentSystem Engine )
set(LINKED_LIBS Plugins ComponentSystem )
set(DEPENDS_ON_TARGETS ${LINKED_LIBS} )

if(WIN32)
    if(MINGW)
        list(APPEND LINKED_LIBS boost_regex_mingw32)
    elseif(MSVC)
        list(APPEND LINKED_LIBS libboost_regex_msvc)
    endif(MINGW)
else(WIN32)
    list(APPEND LINKED_LIBS boost_regex)
endif(WIN32)

include(${MODULE_TEMPLATE_CMAKELISTS_FILE})
