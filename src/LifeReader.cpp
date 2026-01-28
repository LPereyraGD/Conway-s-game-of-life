#include "LifeReader.h"
#include <cctype>
#include <sstream>
#include <stdexcept>
#include <string>

namespace {

std::string trim(const std::string &s) {
  const auto start = s.find_first_not_of(" \t\r\n");
  if (start == std::string::npos)
    return "";
  const auto end = s.find_last_not_of(" \t\r\n");
  return s.substr(start, end - start + 1);
}

} // namespace

std::vector<Cell> LifeReader::Parse(std::istream &in) {
  std::vector<Cell> cells;
  std::string line;
  bool header_seen = false;
  int line_no = 0;

  while (std::getline(in, line)) {
    line_no++;
    const std::string t = trim(line);
    if (t.empty())
      continue;

    if (!header_seen) {
      if (t != "#Life 1.06")
        throw std::runtime_error("Invalid Life 1.06: missing or invalid header (expected \"#Life 1.06\")");
      header_seen = true;
      continue;
    }

    if (t[0] == '#')
      continue;

    std::istringstream ss(line);
    int64_t x = 0, y = 0;
    if (!(ss >> x >> y))
      throw std::runtime_error("Invalid Life 1.06: expected \"x y\" at line " + std::to_string(line_no) + ": " + line);

    std::string rest;
    std::getline(ss, rest);
    for (unsigned char c : rest)
      if (!std::isspace(c))
        throw std::runtime_error("Invalid Life 1.06: expected \"x y\" at line " + std::to_string(line_no) + ": " + line);

    cells.push_back({x, y});
  }

  if (!header_seen)
    throw std::runtime_error("Invalid Life 1.06: missing or invalid header (expected \"#Life 1.06\")");

  return cells;
}
