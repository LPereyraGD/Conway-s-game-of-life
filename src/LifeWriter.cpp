#include "LifeWriter.h"
#include <algorithm>
#include <vector>

void LifeWriter::Write(std::ostream &out, const WorldState &state) {
  out << "#Life 1.06\n";

  std::vector<Cell> sorted_cells(state.begin(), state.end());
  std::sort(sorted_cells.begin(), sorted_cells.end());

  for (const auto &cell : sorted_cells) {
    out << cell.x << " " << cell.y << "\n";
  }
}
