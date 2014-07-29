macro(setup_pch_support)
	if(COMPILER_IS_GCC)

		if(USED_COMPILER_VERSION MATCHES "4\\.[0-9]\\.[0-9]")
			set(COMPILER_SUPPORTS_PCH true)
		else(USED_COMPILER_VERSION MATCHES "4\\.[0-9]\\.[0-9]")
		if(USED_COMPILER_VERSION MATCHES "3\\.4\\.[0-9]")
			set(COMPILER_SUPPORTS_PCH true)
		endif(USED_COMPILER_VERSION MATCHES "3\\.4\\.[0-9]")
		endif(USED_COMPILER_VERSION MATCHES "4\\.[0-9]\\.[0-9]")
		
	elseif(COMPILER_IS_CLANG)

		set(COMPILER_SUPPORTS_PCH true)
		
	elseif(COMPILER_IS_MSVC)

		set(COMPILER_SUPPORTS_PCH true)
		set(COMPILER_NATIVE_PCH_SUPPORT true)
		
	endif(COMPILER_IS_GCC)
endmacro(setup_pch_support)

macro(setup_pch_cflags)
	if(COMPILER_IS_GCC)

		#	if(LINKAGE STREQUAL SHARED OR LINKAGE STREQUAL STATIC)
		#		list(APPEND PCH_COMPILE_FLAGS " -fPIC " )
		#		list(APPEND CMAKE_CXX_FLAGS " -fPIC ")
		#	endif(LINKAGE STREQUAL SHARED OR LINKAGE STREQUAL STATIC)

	elseif(COMPILER_IS_CLANG)

		
		
	elseif(COMPILER_IS_MSVC)
	# nothing - there is native way
		
	endif(COMPILER_IS_GCC)
endmacro(setup_pch_cflags)

macro(setup_pch_command pch_input pch_output)

	set_pch_cflags()

	if(COMPILER_IS_GCC)
		set(PCH_COMMAND ${CMAKE_CXX_COMPILER} ${CMAKE_CXX_FLAGS} ${PCH_COMPILE_FLAGS} -x c++-header -o ${pch_output} -c ${pch_input})
	elseif(COMPILER_IS_CLANG)
		set(PCH_COMMAND ${CMAKE_CXX_COMPILER} ${CMAKE_CXX_FLAGS} ${PCH_COMPILE_FLAGS} -x c++-header -o ${pch_output} -c ${pch_input})
	elseif(COMPILER_IS_MSVC)
		# nothing - there is native way
	endif(COMPILER_IS_GCC)

endmacro(setup_pch_command)

macro(setup_native_pch_support target_name pch_input_h pch_input_cpp)

	if(COMPILER_IS_MSVC)
		GET_TARGET_PROPERTY(oldProps ${target_name} COMPILE_FLAGS)
		
		if (${oldProps} MATCHES NOTFOUND)
		SET(oldProps "")
		endif(${oldProps} MATCHES NOTFOUND)

		SET(newProperties "${oldProps} /Yu\"${pch_input_h}\" /FI\"${pch_input_h}\"")
		SET_TARGET_PROPERTIES(${target_name} PROPERTIES COMPILE_FLAGS "${newProperties}")

		#also include ${oldProps} to have the same compile options
		SET_SOURCE_FILES_PROPERTIES(${pch_input_cpp} PROPERTIES COMPILE_FLAGS "${oldProps} /Yc\"${pch_input_h}\"")
	endif(COMPILER_IS_MSVC)
	
endmacro(setup_native_pch_support)

