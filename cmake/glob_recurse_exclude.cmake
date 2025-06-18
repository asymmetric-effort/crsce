# file: cmake/glob_recurse_exclude.cmake
# (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

function(glob_recurse_exclude out_var root pattern exclude_regex)
    file(GLOB_RECURSE _tmp RELATIVE "${root}" "${pattern}")
    list(FILTER _tmp EXCLUDE REGEX "${exclude_regex}")
    # convert back to absolute paths if you like:
    foreach(_f IN LISTS _tmp)
        list(APPEND _out "${root}/${_f}")
    endforeach()
    set(${out_var} "${_out}" PARENT_SCOPE)
endfunction()
