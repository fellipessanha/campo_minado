#include "context.h"

namespace minesweeper
{

  void Context::minecheck()
  {
    for (unsigned i = 0; i < table.size(); i++)
    {
      if (table.at(i))
      {
        warn.at(i) = 9;
      }
      else
      {

        // mines top
        if (i >= xmax)
        {
          // top left
          if (i % xmax != 0 && table.at(i - 1 - xmax))
            warn.at(i)++;

          // top
          if (table.at(i - xmax))
            warn.at(i)++;

          // top right
          if (i % xmax != xmax - 1 && table.at(i + 1 - xmax))
            warn.at(i)++;
        }

        // left
        if ((i % xmax != 0) && table.at(i - 1))
          warn.at(i)++;

        // right
        if ((i % xmax) != (xmax - 1) && table.at(i + 1))
          warn.at(i)++;

        // mines bot
        if (i < ymax * (xmax - 1))
        {
          // bot left
          if (i % xmax != 0 && table.at(i - 1 + xmax))
            warn.at(i)++;
          // bot
          if (table.at(i + xmax))
            warn.at(i)++;
          // bot right
          if (i % xmax != (xmax - 1) && table.at(i + 1 + xmax))
            warn.at(i)++;
        }
      }
    }
  }

  void Context::eventcheck(unsigned coord)
  {

    if (warn.at(coord) == 9)
    {
      defeat();
    }
    else
    {
      // this makes it so the selected
      table.at(coord) == !table.at(coord);

      if (warn.at(coord) == 0)
      {
        // mines top
        if (coord >= xmax)
        {
          // top left
          if (coord % xmax != 0)
            eventcheck(coord - 1 - xmax);

          // top
          eventcheck(coord - xmax);

          // top right
          if (coord % xmax != xmax - 1)
            eventcheck(coord + 1 - xmax);
        }

        // left
        if ((coord % xmax != 0))
          eventcheck(coord - 1);

        // right
        if ((coord % xmax) != (xmax - 1))
          eventcheck(coord + 1);

        // mines bot
        if (coord < ymax * (xmax - 1))
        {
          // bot left
          if (coord % xmax != 0)
            eventcheck(coord - 1 + xmax);
          // bot
          eventcheck(coord + xmax);
          // bot right
          if (coord % xmax != (xmax - 1))
            eventcheck(coord + 1 + xmax);
        }
      }
    }
  }

  Context::Context(difficulty X)
  {
    switch (X)
    {
    case difficulty::B:
      xmax = 9;
      ymax = 9;
      minecount = 10;
      break;
    case difficulty::I:
      xmax = 15;
      ymax = 13;
      minecount = 40;
      break;
    case difficulty::A:
      xmax = 24;
      ymax = 24;
      minecount = 99;
      break;
    case difficulty::E:
      xmax = 30;
      ymax = 16;
      minecount = 99;
      break;
    }
    while (table.size() != xmax * ymax)
    {
      warn.push_back(0);
      table.push_back(false);
    }
    std::cout << "sz: " << table.size() << "\n";

    // creating random bombs
    createRandomBombs(40);

    // creating helping numbers
    minecheck();

    // sets the table to be used for the gameplay
    for (bool i: table)
      i = false;
  }

  void Context::createRandomBombs(unsigned initial_click_index)
  {
    std::vector<int> index_v(table.size());
    for (size_t i = 0; i < index_v.size(); ++i)
    {
      index_v[i] = i;
    }
    index_v.erase(index_v.begin() + initial_click_index);

    for (unsigned i = 0; i < minecount; ++i)
    {
      auto random_index = rand() % index_v.size();
      auto index = index_v[random_index];
      index_v.erase(index_v.begin() + random_index);
      table[index] = true;
    }
  }

  Context::Context(unsigned x, unsigned y, unsigned m)
      : xmax(x), ymax(y), minecount(m)
  {
    while (table.size() != xmax * ymax)
    {
      warn.push_back(0);
      table.push_back(false);
    }
    std::cout << "sz: " << table.size() << "\n";

    createRandomBombs(45);

    minecheck();
  }

  void Context::defeat()
  {
    for (unsigned i = 0; i < table.size(); i++)
    {
      if (!table.at(i))
      {
        if (i % xmax == xmax - 1)
        {
          std::cout << warn.at(i) << "\n";
        }
        else
          std::cout << warn.at(i) << " ";
      }
      else
      {
        if (i % xmax == xmax - 1)
        {
          std::cout << "*"
                    << "\n";
        }
        else
          std::cout << "*"
                    << " ";
      }
    }
    std::cout << "\n\n";
  }

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

} // namespace minesweeper