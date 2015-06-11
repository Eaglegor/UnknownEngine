message(STATUS "### Building Endoscopy module ###")

list(APPEND INCLUDED_HEADERS ${UNKNOWN_ENGINE_SOURCE_DIR}/Endoscopy/ESCommon)

add_subdirectory(ESInstrumentAlgorithmsPlugin)
add_subdirectory(ESInstrumentHardwarePlugin)
add_subdirectory(ESGUIPlugin)

add_subdirectory(Cases)

set(MODULES_TO_BUILD ${MODULES_TO_BUILD} PARENT_SCOPE)
