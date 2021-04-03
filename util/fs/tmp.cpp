#include "util/fs/tmp.hpp"

#include <ctime>

#include "util/msg/msg.hpp"

#if _WIN32
#include <process.h>
#else  // ^^^ _WIN32 / !_WIN32 vvv
#include <sys/types.h>
#include <unistd.h>
#endif  // ^^^ !_WIN32

namespace util::fs {

namespace {

const char CHARACTERS[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_";

inline constexpr uint64_t fnv_hash(const uint8_t bytes[], const size_t length) {
  uint64_t hash = 0xcbf29ce484222325;
  for (int i = 0; i < length; ++i) {
    hash ^= bytes[i];
    hash *= 0x00000100000001B3;
  }
  return hash;
}

}  // namespace

TemporaryDirectory::TemporaryDirectory() {
  path_ = std::filesystem::temp_directory_path();

  union {
    struct {
      uint64_t now;
      uint32_t pid;
    };
    uint8_t bytes[sizeof(uint64_t) + sizeof(uint32_t)];
  } seed;
  seed.now = time(nullptr);
  seed.pid = getpid();

  // Try (up to 16 times) to find and create a directory with a name that does not exist.
  for (int i = 0; i < 16; ++i) {
    uint64_t rand = fnv_hash(seed.bytes, sizeof(seed));

    // Update part of the seed with the result of the previous hash in order to produce new random
    // values on the next iteration.
    seed.now = rand;

    char buffer[9];
    for (int i = 0; i < 8; ++i) {
      buffer[i] = CHARACTERS[rand & 63];
      rand >>= 6;
    }
    buffer[8] = '\0';

    const auto tmp_path = path_ / buffer;
    if (std::filesystem::create_directory(tmp_path)) {
      path_ = tmp_path;
      return;
    }
  }

  msg::fatal("failed to create a temporary directory");
}

TemporaryDirectory::~TemporaryDirectory() { std::filesystem::remove_all(path_); }

}  // namespace util::fs
