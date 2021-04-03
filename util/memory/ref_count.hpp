#pragma once

#include <cstdint>  // uint32_t
#include <cstdlib>  // calloc, free
#include <new>
#include <utility>

#include "util/msg/msg.hpp"

namespace util::memory {

template <typename T>
class Ref;

template <typename T>
struct RefCounted {
private:
  uint32_t ref_count_;

#if __has_attribute(alignas)

  [[alignas(T)]] uint8_t value_[0];

#else  // ^^^ __has_attribute(alignas) / !__has_attribute(alignas) vvv

  alignas(alignof(T)) uint8_t value_[0];

#endif  // ^^^ !__has_attribute(alignas)

public:
  constexpr RefCounted() = delete;

  RefCounted(const RefCounted&) = delete;
  RefCounted& operator=(const RefCounted&) = delete;

  RefCounted(RefCounted&& other) = delete;
  RefCounted& operator=(RefCounted&& other) = delete;

  ~RefCounted() { ptr()->~T(); }

private:
  friend class Ref<T>;

  template <typename... Args>
  static RefCounted* make(Args&&... args) {
    RefCounted* self = reinterpret_cast<RefCounted*>(calloc(1, sizeof(RefCounted) + sizeof(T)));
    self->ref_count_ = 1;
    new (self->value_) T(std::forward<Args>(args)...);
    return self;
  }

  [[nodiscard]] constexpr T* ptr() { return reinterpret_cast<T*>(value_); }

  void retain() { ++ref_count_; }

  void release() {
    --ref_count_;
    if (ref_count_ == 0) {
      free(this);
    }
  }
};

template <typename T>
class Ref {
  RefCounted<T>* ref_ = nullptr;

public:
  template <typename... Args>
  static Ref make(Args&&... args) {
    return RefCounted<T>::make(std::forward<Args>(args)...);
  }

  constexpr Ref() = default;

  constexpr Ref(const Ref& other) : ref_(other.ref_) { retain(); }

  constexpr Ref& operator=(const Ref& other) {
    // TODO: Fix this to support `a = a;` which will release before trying to retain null.
    release();
    ref_ = other.ref_;
    retain();
    return *this;
  }

  constexpr Ref(Ref&& other) : ref_(other.ref_) { other.ref_ = nullptr; }

  constexpr Ref& operator=(Ref&& other) {
    release();
    ref_       = other.ref_;
    other.ref_ = nullptr;
    return *this;
  }

  template <typename DerivedT>
  constexpr Ref(const Ref<DerivedT>& other) : ref_(reinterpret_cast<RefCounted<T>*>(other.ref_)) {
    retain();
  }

  template <typename DerivedT>
  constexpr Ref& operator=(const Ref<DerivedT>& other) {
    // TODO: Fix this to support `a = a;` which will release before trying to retain null.
    release();
    ref_ = reinterpret_cast<RefCounted<T>*>(other.ref_);
    retain();
    return *this;
  }

  template <typename DerivedT>
  constexpr Ref(Ref<DerivedT>&& other) : ref_(reinterpret_cast<RefCounted<T>*>(other.ref_)) {
    other.ref_ = nullptr;
  }

  template <typename DerivedT>
  constexpr Ref& operator=(Ref<DerivedT>&& other) {
    release();
    ref_       = reinterpret_cast<RefCounted<T>*>(other.ref_);
    other.ref_ = nullptr;
    return *this;
  }

  ~Ref() { release(); }

  [[nodiscard]] constexpr bool operator==(std::nullptr_t) const { return ref_ == nullptr; }
  [[nodiscard]] constexpr bool operator!=(std::nullptr_t) const { return ref_ != nullptr; }
  [[nodiscard]] constexpr bool operator==(const Ref& other) const { return ref_ == other.ref_; }
  [[nodiscard]] constexpr bool operator!=(const Ref& other) const { return ref_ != other.ref_; }

  [[nodiscard]] constexpr operator T&() {
#ifndef NDEBUG
    if (ref_ == nullptr) {
      util::msg::fatal("dereferencing null reference");
    }
#endif  // ^^^ !defined(NDEBUG)
    return *ref_->ptr();
  }
  [[nodiscard]] constexpr T* operator->() {
#ifndef NDEBUG
    if (ref_ == nullptr) {
      util::msg::fatal("dereferencing null reference");
    }
#endif  // ^^^ !defined(NDEBUG)
    return ref_->ptr();
  }

  [[nodiscard]] constexpr          operator const T&() const { return *ref_->ptr(); }
  [[nodiscard]] constexpr const T* operator->() const { return ref_->ptr(); }

private:
  template <typename>
  friend class Ref;

  constexpr Ref(RefCounted<T>* ref) : ref_(ref) {}

  constexpr void retain() {
    if (ref_ != nullptr) {
      ref_->retain();
    }
  }

  constexpr void release() {
    if (ref_ != nullptr) {
      ref_->release();
      ref_ = nullptr;
    }
  }
};

}  // namespace util::memory
