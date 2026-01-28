#include "GameWorld.h"

#include <climits>
#include <optional>
#include <unordered_map>

namespace {

constexpr size_t kNeighborReserveFactor = 4;

std::optional<int64_t> SafeAdd(int64_t a, int64_t delta) {
  if (delta > 0) {
    if (a > INT64_MAX - delta) return std::nullopt;
  } else if (delta < 0) {
    if (a < INT64_MIN - delta) return std::nullopt;
  }
  return a + delta;
}

}

GameWorld::GameWorld() {}

void GameWorld::Initialize(const std::vector<Cell> &initial_state) {
  live_cells_.clear();
  for (const auto &cell : initial_state) {
    live_cells_.insert(cell);
  }
}

const WorldState &GameWorld::GetLiveCells() const { return live_cells_; }

size_t GameWorld::Population() const { return live_cells_.size(); }

void GameWorld::Tick() {
  std::unordered_map<Cell, int, CellHash> neighbor_counts;
  neighbor_counts.reserve(live_cells_.size() * kNeighborReserveFactor);

  for (const auto &cell : live_cells_) {
    for (int64_t dy = -1; dy <= 1; ++dy) {
      for (int64_t dx = -1; dx <= 1; ++dx) {
        if (dx == 0 && dy == 0)
          continue;

        auto neighbor_x = SafeAdd(cell.x, dx);
        auto neighbor_y = SafeAdd(cell.y, dy);
        if (!neighbor_x || !neighbor_y) continue;

        Cell neighbor = {*neighbor_x, *neighbor_y};
        neighbor_counts[neighbor]++;
      }
    }
  }

  WorldState next_generation;
  next_generation.reserve(live_cells_.size());

  for (const auto &[cell, count] : neighbor_counts) {
    if (count == 3) {
      next_generation.insert(cell);
    } else if (count == 2) {
      if (live_cells_.count(cell)) {
        next_generation.insert(cell);
      }
    }
  }

  live_cells_ = std::move(next_generation);
}
