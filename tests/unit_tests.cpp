#include "GameWorld.h"
#include <cassert>
#include <iostream>
#include <sstream>

void TestBlockPattern() {
  // 2x2 Block is a still life
  // 0 0
  // 0 1
  // 1 0
  // 1 1
  std::vector<Cell> cells = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
  GameWorld world;
  world.Initialize(cells);

  world.Tick();

  assert(world.Population() == 4);
  auto live = world.GetLiveCells();
  assert(live.count({0, 0}));
  assert(live.count({1, 1}));
  std::cout << "[PASS] TestBlockPattern" << std::endl;
}

void TestBlinkerPattern() {
  // Blinker Period 2
  // Vertical: (0,0), (0,1), (0,2)
  // Becomes Horizontal: (-1,1), (0,1), (1,1)
  std::vector<Cell> cells = {{0, 0}, {0, 1}, {0, 2}};
  GameWorld world;
  world.Initialize(cells);

  world.Tick();

  assert(world.Population() == 3);
  auto live = world.GetLiveCells();
  assert(live.count({-1, 1}) && live.count({0, 1}) && live.count({1, 1}));

  world.Tick();
  // Should be back to vertical
  live = world.GetLiveCells();
  assert(live.count({0, 0}) && live.count({0, 1}) && live.count({0, 2}));

  std::cout << "[PASS] TestBlinkerPattern" << std::endl;
}

void TestLargeCoordinates() {
  // Test extremely large coordinates to ensure no overflow crashes or bad
  // hashing Using coordinates from the prompt example
  int64_t base = -2000000000000;
  std::vector<Cell> cells = {
      {base, base}, {base - 1, base - 1}, {base, base - 1}};
  // L-shape of 3 cells.
  //  . .
  //  x x (base-1, base-1), (base, base-1)
  //  . x (base, base)

  // Checking neighbors:
  // (base, base-1) has 2 neighbors (base-1, base-1) and (base, base). Stays
  // live.
  // ...

  GameWorld world;
  world.Initialize(cells);
  world.Tick();

  // We mainly want to ensure it runs and returns a valid state
  assert(world.Population() ==
         4); // This L-shape evolves to a 2x2 block usually
  // Let's check exactly. L-shape creates a block.
  // New cell at (base-1, base) should be born (3 neighbors)
  std::cout << "[PASS] TestLargeCoordinates" << std::endl;
}

void TestEmptyWorld() {
  std::vector<Cell> cells = {};
  GameWorld world;
  world.Initialize(cells);
  world.Tick();
  assert(world.Population() == 0);
  assert(world.GetLiveCells().empty());
  std::cout << "[PASS] TestEmptyWorld" << std::endl;
}

void TestSingleCell() {
  // Single cell has < 2 neighbors, dies in one tick
  std::vector<Cell> cells = {{0, 0}};
  GameWorld world;
  world.Initialize(cells);
  world.Tick();
  assert(world.Population() == 0);
  std::cout << "[PASS] TestSingleCell" << std::endl;
}

int main() {
  TestBlockPattern();
  TestBlinkerPattern();
  TestLargeCoordinates();
  TestEmptyWorld();
  TestSingleCell();
  return 0;
}
