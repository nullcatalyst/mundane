#pragma once

#include <cstdlib>
#include <iostream>

namespace util::msg {

template <typename... Args>
[[noreturn]] inline void fatal(Args&&... args) {
  (std::cerr << ... << args) << std::endl;
  abort();
}

template <typename... Args>
inline void info(Args&&... args) {
  (std::cout << ... << args) << std::endl;
}

template <typename... Args>
inline void debug(Args&&... args) {
#if MSG_DEBUG_PRINT
  (std::cout << ... << args) << std::endl;
#endif  // NDEBUG
}

}  // namespace util::msg
