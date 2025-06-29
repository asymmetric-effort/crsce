/**
 * @file include/utils/is_valid_block_size.h
 * @brief define the is_valid_block_size() function
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#pragma once

/**
 * @name is_valid_block_size
 * @brief Check if a given block size is supported by CRSCE.
 * @param s  The side length (in elements) of the CSM block.
 * @return bool `true` if `s` is one of the supported block sizes (512, 1024, 2048, 4096); `false` otherwise.
 * @ref docs/CRSCE-2025-v1.docx page 59-65.
 */
inline bool is_valid_block_size(const unsigned s) {
    switch (s) {
    case 512:
    case 1024:
    case 2048:
    case 4096:
        return true;
    default:
        return false;
    }
}
