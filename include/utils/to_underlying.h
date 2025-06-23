/**
 * @file: include/utils/to_underlying.h
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */
#pragma once
#include <type_traits>

namespace std {

    /**
     * @brief Convert a scoped enum to its underlying integral type.
     * @tparam E Enum type (must be scoped enum)
     * @param e Enum value
     * @return Underlying integral representation
     */
    template <typename E>
    constexpr auto to_underlying(E e) noexcept -> std::underlying_type_t<E> {
        static_assert(std::is_enum_v<E>, "to_underlying requires enum type");
        return static_cast<std::underlying_type_t<E>>(e);
    }

} // namespace std
