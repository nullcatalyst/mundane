#pragma once

#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>

#include "util/msg/msg.hpp"

namespace util::fs {

inline std::string read_file_string(const std::string& file_name) {
  std::ifstream file(file_name);
  if (!file) {
    msg::fatal("file [", file_name, "] not found");
  }

  std::string contents;
  file.seekg(0, std::ios::end);
  contents.reserve(file.tellg());
  file.seekg(0, std::ios::beg);

  contents.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
  return contents;
}

inline std::vector<uint8_t> read_file_binary(const std::string& file_name) {
  std::ifstream file(file_name, std::ios::binary);
  if (!file) {
    msg::fatal("file [", file_name, "] not found");
  }

  std::vector<uint8_t> contents;
  file.seekg(0, std::ios::end);
  contents.resize(file.tellg());
  file.seekg(0, std::ios::beg);
  file.read(reinterpret_cast<char*>(contents.data()), contents.size());
  return contents;
}

}  // namespace util::fs
