# file: cmake/lint_markdown.cmake
# (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

# Markdown lint
find_program(MARKDOWNLINT markdownlint)

if(MARKDOWNLINT)
    file(GLOB_RECURSE MD_FILES "${CMAKE_SOURCE_DIR}/*.md")
    add_custom_target(lint_markdown
            COMMAND ${MARKDOWNLINT} --config ../.markdownlint.json ${MD_FILES} || exit 1
            COMMENT "Linting Markdown files"
    )
else()
    message(WARNING "markdownlint not found; skipping lint_markdownlint target")
endif()
