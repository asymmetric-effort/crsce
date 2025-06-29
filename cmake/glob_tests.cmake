# Glob all test programs
file(GLOB_RECURSE TEST_PROGRAMS
        CONFIGURE_DEPENDS
        "${PROJECT_ROOT}/test/*.cpp")

set(_script "${CMAKE_BINARY_DIR}/list_tests.cmake")
file(WRITE ${_script}
        "set(TEST_PROGRAMS ${TEST_PROGRAMS})\n"
        "set(test_count 0)\n"
        "foreach(testfile IN LISTS TEST_PROGRAMS)\n"
        "  math(EXPR test_count \"\${test_count} + 1\")\n"
        "  message(STATUS \" \${test_count}: \${testfile}\")\n"
        "endforeach()\n"
        "message(STATUS \"Total test programs found: \${test_count}\")\n"
)

# 2) Expose a custom target that runs it:
add_custom_target(list_tests
        COMMAND ${CMAKE_COMMAND} -P ${_script}
        COMMENT "Printing all TEST_PROGRAMS with indices…"
)
