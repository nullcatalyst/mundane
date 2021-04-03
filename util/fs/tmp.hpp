#pragma once

#include <filesystem>

namespace util::fs {

class TemporaryDirectory {
  std::filesystem::path path_;

public:
  TemporaryDirectory();

  TemporaryDirectory(const TemporaryDirectory&) = delete;
  TemporaryDirectory& operator=(const TemporaryDirectory&) = delete;

  TemporaryDirectory(TemporaryDirectory&&) = delete;
  TemporaryDirectory& operator=(TemporaryDirectory&&) = delete;

  ~TemporaryDirectory();

  [[nodiscard]] constexpr const std::filesystem::path& path() const { return path_; }

  [[nodiscard]] operator std::string() const { return path_.string(); }
};

}  // namespace util::fs
