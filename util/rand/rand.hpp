#pragma once

#include <cstdint>
#include <ctime>

#include "wyhash/wyhash.h"

namespace util::rand {

class Random {
  uint64_t seed_;

public:
  static Random from_current_time() { return Random(static_cast<uint64_t>(time(nullptr))); }

  constexpr Random() : seed_(0) {}
  constexpr Random(uint64_t seed) : seed_(seed) {}

  uint64_t next_u64() { return wyrand(&seed_); }
  uint32_t next_u32() { return static_cast<uint32_t>(next_u64()); }
  uint16_t next_u16() { return static_cast<uint16_t>(next_u64()); }
  uint8_t  next_u8() { return static_cast<uint8_t>(next_u64()); }

  int64_t next_i64() { return static_cast<int64_t>(next_u64()); }
  int32_t next_i32() { return static_cast<int32_t>(next_u64()); }
  int16_t next_i16() { return static_cast<int16_t>(next_u64()); }
  int8_t  next_i8() { return static_cast<int8_t>(next_u64()); }

  char next_char() { return static_cast<char>(next_u64()); }
  bool next_bool() { return (next_u64() & 1) == 1; }

  // Returns a floating point value in the range [0.0, 1.0), with 23 bits of randomness.
  float next_f32() {
    union {
      uint32_t u32_value;
      float    f32_value;
      struct {
        unsigned sign : 1;
        unsigned exponent : 8;
        unsigned mantissa : 23;
      };
    } value;

    // Start off with the binary representation for the value of `1.0f`, then set the mantissa bits
    // to any value (these bits are the output random value). The value at this point will be in the
    // range [1.0, 2.0). Then sutract the initial value of `1.0f`. This allows us to avoid any
    // floating point denormalization issues and have the hardware do that for us.
    value.sign     = 0;
    value.exponent = 127;
    value.mantissa = next_u64();
    return value.f32_value - 1.0f;
  }

  // Returns a floating point value in the range [0.0, 1.0), with 52 bits of randomness.
  float next_f64() {
    union {
      uint32_t u64_value;
      double   f64_value;
      struct {
        unsigned sign : 1;
        unsigned exponent : 11;
        unsigned mantissa : 52;
      };
    } value;

    // Start off with the binary representation for the value of `1.0`, then set the mantissa bits
    // to any value (these bits are the output random value). The value at this point will be in the
    // range [1.0, 2.0). Then sutract the initial value of `1.0`. This allows us to avoid any
    // floating point denormalization issues and have the hardware do that for us.
    value.sign     = 0;
    value.exponent = 1023;
    value.mantissa = next_u64();
    return value.f64_value - 1.0;
  }
};

}  // namespace util::rand
