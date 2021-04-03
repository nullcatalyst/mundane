#pragma once

#include <initializer_list>
#include <string>
#include <string_view>

namespace util::fs {

constexpr const std::string_view DIR_SEPERATOR = "/";

inline std::string path_join(const std::string_view a, const std::string_view b) {
  std::string result;
  result.reserve(a.size() + DIR_SEPERATOR.size() + b.size());

  if (a.size() != 0) {
    result.assign(a);
  }
  if (a.size() != 0 && b.size() != 0) {
    result.append(DIR_SEPERATOR);
  }
  result.append(b);

  return result;
}

inline std::string path_join(const std::initializer_list<std::string_view> parts) {
  std::string result;

  size_t length = DIR_SEPERATOR.size() * (parts.size() - 1);
  for (const auto& part : parts) {
    length += part.size();
  }
  result.reserve(length);

  bool first = true;
  for (const auto& part : parts) {
    if (part.size() == 0) {
      continue;
    }

    if (first) {
      first = false;
      result.assign(part);
      continue;
    }

    result.append(DIR_SEPERATOR);
    result.append(part);
  }

  return result;
}

inline std::string replace_extension(const std::string_view path, const std::string_view ext,
                                     const std::string_view new_ext) {
  std::string result;

  if (path.size() <= ext.size() || std::equal(ext.rbegin(), ext.rend(), path.rbegin())) {
    result.reserve(path.size() - ext.size() + new_ext.size());
    result.assign(path.substr(0, path.size() - ext.size()));
    result.append(new_ext);
  } else {
    result.reserve(path.size() + new_ext.size());
    result.assign(path);
    result.append(new_ext);
  }

  return result;
}

}  // namespace util::fs
