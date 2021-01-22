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

// shows number of mines of each square
// std::cout << "\n\n";
// for (unsigned i = 0; i < table.size(); i++)
// {
//     if (i % xmax == xmax - 1)
//     {
//         std::cout << warn.at(i) << "\n";
//     }
//     else
//         std::cout << warn.at(i) << " ";
// }

namespace minesweeper
{

class Context
{
  std::vector<bool> table;
  std::vector<unsigned> warn;
  unsigned minecount, xmax, ymax;

  void minecheck();

public:
  Context(difficulty X);
  void createRandomBombs(unsigned initial_click_index);
  // init with custom sizes
  Context(unsigned x, unsigned y, unsigned m);
  void defeat();
};

} // namespace minesweeper