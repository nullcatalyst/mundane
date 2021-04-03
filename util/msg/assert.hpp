#pragma once

#include <cstdlib>
#include <iostream>

#include "util/msg/msg.hpp"

namespace util::msg {

template <typename T, typename... Args>
inline void assert_eq(const T& actual, const T& expected, Args&&... args) {
  if (!(actual == expected)) {
    std::cerr << "assertion failed: " << actual << " must equal " << expected << std::endl;
    (std::cerr << ... << args) << std::endl;
    abort();
  }
}

template <typename T, typename... Args>
inline void assert_ne(const T& actual, const T& expected, Args&&... args) {
  if (!(actual != expected)) {
    std::cerr << "assertion failed: " << actual << " must not equal " << expected << std::endl;
    (std::cerr << ... << args) << std::endl;
    abort();
  }
}

template <typename T, typename... Args>
inline void assert_lt(const T& actual, const T& expected, Args&&... args) {
  if (!(actual < expected)) {
    std::cerr << "assertion failed: " << actual << " must be less than " << expected << std::endl;
    (std::cerr << ... << args) << std::endl;
    abort();
  }
}

template <typename T, typename... Args>
inline void assert_gt(const T& actual, const T& expected, Args&&... args) {
  if (!(actual > expected)) {
    std::cerr << "assertion failed: " << actual << " must be greater than " << expected << std::endl;
    (std::cerr << ... << args) << std::endl;
    abort();
  }
}

template <typename T, typename... Args>
inline void assert_le(const T& actual, const T& expected, Args&&... args) {
  if (!(actual < expected)) {
    std::cerr << "assertion failed: " << actual << " must be less than or equal to " << expected << std::endl;
    (std::cerr << ... << args) << std::endl;
    abort();
  }
}

template <typename T, typename... Args>
inline void assert_ge(const T& actual, const T& expected, Args&&... args) {
  if (!(actual > expected)) {
    std::cerr << "assertion failed: " << actual << " must be greater than or equal to " << expected << std::endl;
    (std::cerr << ... << args) << std::endl;
    abort();
  }
}

}  // namespace util::msg
