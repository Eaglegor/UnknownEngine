set(TARGET_NAME ResourceManager)
set(LINKAGE SHARED)

set(INCLUDED_MODULE_HEADERS ResourceManager Engine Utils LogManager )
set(LINKED_LIBS LogManager )
set(DEPENDS_ON_TARGETS ${LINKED_LIBS} )

find_package(Boost 1.55.0 REQUIRED COMPONENTS system thread)
list(APPEND LINKED_LIBS ${Boost_LIBRARIES})
link_directories(${Boost_LIBRARY_DIRS})

include(${MODULE_TEMPLATE_CMAKELISTS_FILE})
