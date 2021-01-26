#pragma once

// Difficulty settings

// Beginner – 9 * 9 Board and 10 Mines
// Intermediate – 16 * 16 Board and 40 Mines
// Advanced – 24 * 24 Board and 99 Mines

#include <vector>
#include <iostream>

enum class difficulty
{
  B = 1,
  I,
  A,
  E
};

namespace minesweeper
{

class Context
{
  std::vector<bool> table;
  std::vector<unsigned> warn;
  unsigned minecount, xmax, ymax;

  void minecheck();
  void createRandomBombs(unsigned initial_click_index);
  void defeat();

public:

  // inits the standart difficulties
  Context(difficulty X);

  // init with custom sizes
  Context(unsigned x, unsigned y, unsigned m);

  void eventcheck(unsigned coord);
  void show();
  
};

} // namespace minesweeper