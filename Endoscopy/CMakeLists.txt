message(STATUS "### Building Endoscopy module ###")

add_subdirectory(ESAngelScriptBindingPlugin)
add_subdirectory(ESInstrumentAlgorithmsPlugin)
add_subdirectory(ESInstrumentHardwarePlugin)

set(MODULES_TO_BUILD ${MODULES_TO_BUILD} PARENT_SCOPE)
