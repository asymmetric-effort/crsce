# file: cmake/linters.cmake
# (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

# Linting custom targets for the project
include(lint_cpp)
include(lint_yaml)
include(lint_json)
include(lint_makefile)
include(lint_markdown)

# Aggregate lint target
add_custom_target(linters
        DEPENDS
        lint_markdown
        lint_yaml
        lint_json
        lint_makefile
        lint_cpp
        COMMENT "Run all lint checks"
)
