#pragma once

#include <memory>
#include <new>
#include <utility>

namespace util::memory {

template <typename T>
struct VarLenStructPtrDeleter {
  void operator()(T* ptr) {
    ptr->~T();
    free(ptr);
  }
};

template <typename T>
using VarLenStructPtr = std::unique_ptr<T, VarLenStructPtrDeleter<T>>;

template <typename T, typename E, typename... Args>
inline VarLenStructPtr<T> make_var_len_struct_ptr(size_t additional_elements, Args&&... args) {
  void* ptr = ::operator new(sizeof(T) + sizeof(E) * additional_elements);
  return MallocPtr<T>(new (ptr) T(std::forward<Args>(args)...));
}

}  // namespace util::memory
