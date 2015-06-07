macro(add_test_case TestName)

	add_executable(test_${TestName} ${CMAKE_CURRENT_SOURCE_DIR}/test/${TestName})	
	add_test(${TestName} test_${TestName})

endmacro()


macro(add_test_case_with_custom_filename TestName FileName)

	add_executable(test_${TestName} ${CMAKE_CURRENT_SOURCE_DIR}/test/${FileName})
	add_test(${TestName} test_${TestName})

endmacro()