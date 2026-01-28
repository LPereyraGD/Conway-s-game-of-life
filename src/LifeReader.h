#pragma once

#include "Cell.h"
#include <istream>
#include <vector>

class LifeReader {
public:
  static std::vector<Cell> Parse(std::istream &in);
};
