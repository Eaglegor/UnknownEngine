message(STATUS "### Building Endoscopy module ###")

add_subdirectory(ESInstrumentAlgorithmsPlugin)
add_subdirectory(ESInstrumentHardwarePlugin)
add_subdirectory(ESGUIPlugin)

set(MODULES_TO_BUILD ${MODULES_TO_BUILD} PARENT_SCOPE)
