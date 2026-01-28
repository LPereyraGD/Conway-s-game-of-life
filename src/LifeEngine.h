#pragma once

#include "LifeTypes.h"
#include <vector>

class LifeEngine {
public:
  virtual ~LifeEngine() = default;

  virtual void Initialize(const std::vector<Cell> &initial_state) = 0;
  virtual void Tick() = 0;
  virtual const WorldState &GetLiveCells() const = 0;
  virtual size_t Population() const = 0;
};
