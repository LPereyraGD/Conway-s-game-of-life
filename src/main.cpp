#include "GameWorld.h"
#include "LifeReader.h"
#include "LifeWriter.h"
#include <iostream>
#include <string>

static void usage(const char *prog) {
  std::cerr << "Usage: " << prog << " [-n iterations]" << std::endl;
}

int main(int argc, char *argv[]) {
  int iterations = 10;

  if (argc == 3 && std::string(argv[1]) == "-n") {
    try {
      iterations = std::stoi(argv[2]);
      if (iterations < 1) {
        usage(argv[0]);
        return 1;
      }
    } catch (...) {
      usage(argv[0]);
      return 1;
    }
  } else if (argc != 1) {
    usage(argv[0]);
    return 1;
  }

  try {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto initial_cells = LifeReader::Parse(std::cin);
    GameWorld world;
    world.Initialize(initial_cells);

    for (int i = 0; i < iterations; ++i)
      world.Tick();

    LifeWriter::Write(std::cout, world.GetLiveCells());
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
