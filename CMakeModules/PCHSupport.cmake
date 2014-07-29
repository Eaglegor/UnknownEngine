
include(${UNKNOWN_ENGINE_SOURCE_DIR}/CMakeModules/DetectCompilerPCHSupport.cmake)

setup_pch_support()

if(NOT COMPILER_SUPPORTS_PCH)
  message("Precompiled headers not supported for this compiler")
endif(NOT COMPILER_SUPPORTS_PCH)

macro(add_precompiled_header pch_target_name pch_h_file pch_cpp_file)
	
	if(COMPILER_NATIVE_PCH_SUPPORT)
		add_precompiled_header_native(${pch_target_name} ${pch_h_file} ${pch_cpp_file})
	else(COMPILER_NATIVE_PCH_SUPPORT)
		add_precompiled_header_not_native(${pch_target_name} ${pch_h_file} ${pch_cpp_file})
	endif(COMPILER_NATIVE_PCH_SUPPORT)
	
endmacro(add_precompiled_header)


macro(add_precompiled_header_not_native pch_target_name pch_h_file pch_cpp_file)

	setup_pch_output_name(${pch_target_name})
	setup_pch_command( ${pch_h_file} ${PCH_OUTPUT_FILE} )
	
	add_custom_command(OUTPUT ${PCH_OUTPUT_FILE} COMMAND ${PCH_COMMAND} DEPENDS ${pch_h_file})
	
	add_target_dependency(${pch_target_name})
	
endmacro(add_precompiled_header_not_native)


macro(add_precompiled_header_native pch_target_name pch_h_file pch_cpp_file)

	setup_native_pch_support(${pch_target_name} ${pch_h_file} ${pch_cpp_file})
	
endmacro(add_precompiled_header_native)




macro(setup_pch_output_name pch_target_name)

	if(COMPILER_IS_GCC)
		set(PCH_OUTPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/${pch_target_name}.gch")
	elseif(COMPILER_IS_CLANG OR COMPILER_IS_MSVC)
		set(PCH_OUTPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/${pch_target_name}.pch")
	endif(COMPILER_IS_GCC)

endmacro(setup_pch_output_name)




macro(add_target_dependency _targetName )
	add_custom_target("pch_Generate_${_targetName}" DEPENDS ${PCH_OUTPUT_FILE} )

	add_dependencies(${_targetName} "pch_Generate_${_targetName}" )
endmacro(add_target_dependency)
