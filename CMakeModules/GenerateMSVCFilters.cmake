macro(MSVC_generate_filters)

	# Glob all sources file inside directory ${DIRECTORY}
	file(GLOB_RECURSE TMP_FILES
		${CMAKE_CURRENT_SOURCE_DIR}/*.h
		${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/*.c
		${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	)

	foreach(f ${TMP_FILES})
		# Get the path of the file relative to ${DIRECTORY},
		# then alter it (not compulsory)
		file(RELATIVE_PATH SRCGR ${CMAKE_CURRENT_SOURCE_DIR} ${f})

		# Extract the folder, ie remove the filename part
		string(REGEX REPLACE "(.*)(/[^/]*)$" "\\1" SRCGR ${SRCGR})

		# Source_group expects \\ (double antislash), not / (slash)
		string(REPLACE / \\ SRCGR ${SRCGR})
		source_group("${SRCGR}" FILES ${f})
	endforeach()

endmacro(MSVC_generate_filters)
