#pragma once

#include "Cell.h"
#include <unordered_set>

using WorldState = std::unordered_set<Cell, CellHash>;
