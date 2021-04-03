#pragma once

#define BIT_FLAG($enum_type, $sized_type)                                                     \
  constexpr inline $enum_type operator~($enum_type a) noexcept {                               \
    return static_cast<$enum_type>(~static_cast<$sized_type>(a));                              \
  }                                                                                            \
  constexpr inline $enum_type operator&($enum_type a, $enum_type b) noexcept {                 \
    return static_cast<$enum_type>(static_cast<$sized_type>(a) & static_cast<$sized_type>(b)); \
  }                                                                                            \
  constexpr inline $enum_type operator|($enum_type a, $enum_type b) noexcept {                 \
    return static_cast<$enum_type>(static_cast<$sized_type>(a) | static_cast<$sized_type>(b)); \
  }                                                                                            \
  constexpr inline $enum_type operator^($enum_type a, $enum_type b) noexcept {                 \
    return static_cast<$enum_type>(static_cast<$sized_type>(a) ^ static_cast<$sized_type>(b)); \
  }                                                                                            \
  constexpr inline $enum_type& operator|=($enum_type& a, $enum_type b) noexcept {              \
    a = a | b;                                                                                 \
    return a;                                                                                  \
  }                                                                                            \
  constexpr inline $enum_type& operator&=($enum_type& a, $enum_type b) noexcept {              \
    a = a & b;                                                                                 \
    return a;                                                                                  \
  } \
  constexpr inline $enum_type& operator^=($enum_type& a, $enum_type b) noexcept {              \
    a = a ^ b;                                                                                 \
    return a;                                                                                  \
  }

#define BIT_FLAG_CONTAINS($a, $b) ((($a) & ($b)) == ($b))
