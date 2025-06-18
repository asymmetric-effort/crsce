# file: cmake/lint_json.cmake
# (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

# JSON lint
find_program(JSON_LINTER jsonlint)
include(glob_recurse_exclude)

if(JSON_LINTER)

    glob_recurse_exclude(
            JSON_FILES
            "${CMAKE_SOURCE_DIR}"
            "*.json"
            ".*/(build|cmake-build-debug|cmake-build-default|cmake-build-release)/.*$"
    )

    # Phony target that runs jsonlint on every file
    add_custom_target(lint_json
            COMMENT "Linting JSON files"
    )

    foreach(f IN LISTS JSON_FILES)
        add_custom_command(
                TARGET            lint_json
                POST_BUILD
                COMMAND           ${JSON_LINTER} -q -p -c "${f}" || exit 1
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                COMMENT           "Linting ${f}"
        )
    endforeach()
else()
    message(WARNING "jsonlint not found; skipping lint_json target")
endif()
