#pragma once

#include <cstdint>
#include <functional>

struct Cell {
  int64_t x;
  int64_t y;

  bool operator==(const Cell &other) const {
    return x == other.x && y == other.y;
  }

  // For sorting output if needed, or simple deterministic ordering
  bool operator<(const Cell &other) const {
    if (x != other.x)
      return x < other.x;
    return y < other.y;
  }
};

struct CellHash {
  std::size_t operator()(const Cell &c) const {
    return std::hash<int64_t>{}(c.x) ^ (std::hash<int64_t>{}(c.y) << 1);
  }
};
