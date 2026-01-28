#pragma once

#include "LifeEngine.h"

class GameWorld : public LifeEngine {
public:
  GameWorld();

  void Initialize(const std::vector<Cell> &initial_state) override;

  void Tick() override;

  const WorldState &GetLiveCells() const override;

  size_t Population() const override;

private:
  WorldState live_cells_;
};
