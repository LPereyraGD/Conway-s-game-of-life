#pragma once

#include "LifeTypes.h"
#include <ostream>

class LifeWriter {
public:
  // Writes the state in Life 1.06 format
  // Sorts output for deterministic results which is crucial for testing/diffing
  static void Write(std::ostream &out, const WorldState &state);
};
