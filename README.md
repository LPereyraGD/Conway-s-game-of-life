# Conway's Game of Life

A C++17 implementation of Conway's Game of Life that uses a sparse grid—so you can run patterns with huge coordinates without allocating a giant 2D array. Storage is O(N) in the number of live cells.

## Build

CMake 3.14+ and a C++17 compiler.

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

## Usage

Reads from stdin, writes to stdout. Run with a Life 1.06 file:

```bash
./game_of_life < input.life > output.life
```

Or pipe:

```bash
cat sample.in | ./game_of_life
```

To change the number of iterations (default 10):

```bash
./game_of_life -n 20 < input.life
```

Invalid arguments (e.g. `-n` without a number, or `-n 0`) print a short usage message and exit with code 1. Parse errors (missing header, malformed lines) are reported to stderr before exiting.

## Tests

Unit tests live in `tests/`. They cover:

- **Block** (2×2 still life)
- **Blinker** (period-2 oscillator)
- **Large coordinates** (e.g. around ±2×10¹², as in the sample)
- **Empty world** (no cells; still runs a tick, stays empty)
- **Single cell** (dies in one tick)

Run them from the build directory:

```bash
./unit_tests
```

Or via CTest: `ctest` in the build folder.

## Possible improvements

Ideas for extending or tuning the implementation:

- **Multithreading**: Partition live cells (or spatial regions) across threads for neighbor counting and next-generation construction. A thread-safe map or per-thread counts merged at the end would work. Helps for very large, dense patterns.
- **Other formats**: Life 1.05, RLE, or plain (e.g. `*.cells`) for compatibility with more editors and libraries.
- **Stabilization detection**: Track a hash of the world state each tick; stop early if we detect a cycle or fixed point (e.g. still lifes, oscillators).
- **Smarter reserves**: Use a growth heuristic (e.g. from recent population deltas) to better `reserve` the next-generation set for guns, puffers, or other expanding patterns.
- **Visualization**: Optional bounding-box or raster output (e.g. PPM, or ASCII in a terminal) for quick visual checks.
