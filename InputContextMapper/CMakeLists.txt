set(TARGET_NAME InputContextMapper)
set(LINKAGE SHARED)

set(INCLUDED_MODULE_HEADERS InputContextMapper Plugins ComponentSystem Utils Engine UserInput Math LogManager)
set(LINKED_LIBS Engine ComponentSystem Plugins LogManager)
set(DEPENDS_ON_TARGETS ${LINKED_LIBS} )

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/config/ActionSlots.xml DESTINATION ${EXECUTABLE_DEPLOY_DIR}/InputContextMapperConfig)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/config/InputLayout.cfg DESTINATION ${EXECUTABLE_DEPLOY_DIR}/InputContextMapperConfig)

include(${MODULE_TEMPLATE_CMAKELISTS_FILE})
