set(OJ_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/oj-submission)
macro(add_oj_submittable
        TargetName PackageName CppSourceFileName
        )
    add_executable(${TargetName} ${PackageName}/${CppSourceFileName}.cpp)
    add_custom_target(Submit_${TargetName}
            COMMAND ${CMAKE_MAKE_PROGRAM} ${CppSourceFileName}.cpp.i
            COMMAND ${CMAKE_COMMAND} -E copy
            "${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${TargetName}.dir/${CppSourceFileName}.cpp.i"
            "${OJ_OUTPUT_PATH}/${CppSourceFileName}.cpp.i"
            COMMAND notepad.exe "${OJ_OUTPUT_PATH}/${CppSourceFileName}.cpp.i"
            )
endmacro()
