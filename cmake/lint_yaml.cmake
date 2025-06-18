# file: cmake/lint_yaml.cmake
# (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

# YAML lint
find_program(YAMLLINT yamllint)

if(YAMLLINT)
    # Gather all YAML files, excluding anything under the build/ directory
    file(GLOB_RECURSE YAML_FILES
            "${CMAKE_SOURCE_DIR}/*.yml"
            "${CMAKE_SOURCE_DIR}/*.yaml"
    )
    # Remove entries in build/
    list(FILTER YAML_FILES EXCLUDE REGEX ".*/build/.*")

    # Phony target that runs yamllint on each file
    add_custom_target(lint_yaml
            COMMENT "Linting YAML files"
    )
    foreach(f IN LISTS YAML_FILES)
        add_custom_command(
                TARGET            lint_yaml
                POST_BUILD
                COMMAND           ${YAMLLINT} --config-file .yamllint "${f}" || exit 1
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                COMMENT           "Linting ${f}"
        )
    endforeach()
else()
    message(WARNING "yamllint not found; skipping lint_yaml target")
endif()
