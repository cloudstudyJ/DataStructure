#pragma once

namespace TypeHandlerBase {
    template <typename T> struct removeReference      { using type = T; };
    template <typename T> struct removeReference<T&>  { using type = T; };
    template <typename T> struct removeReference<T&&> { using type = T; };
}

template <typename T>
using removeReference = typename TypeHandlerBase::removeReference<T>::type;


template <typename T>
[[nodiscard]] inline constexpr decltype(auto) move(T&& val) noexcept { return static_cast<removeReference<T>&&>(val); }