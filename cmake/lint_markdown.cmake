# file: cmake/lint_markdown.cmake
# (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

# Markdown lint
#find_program(MARKDOWNLINTER pymarkdown)
#
#if(MARKDOWNLINT)
#    file(GLOB_RECURSE MD_FILES "${CMAKE_SOURCE_DIR}/*.md")
#    add_custom_target(lint_markdown
#            COMMAND ${MARKDOWNLINTER} --config ../.markdownlint.json ${MD_FILES} || exit 1
#            COMMENT "Linting Markdown files"
#    )
#else()
#    message(WARNING "markdown linter (${MARKDOWNLINTER}) not found; skipping lint_markdown target")
#endif()
