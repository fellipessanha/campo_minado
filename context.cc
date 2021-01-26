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
    // std::cout << "sz: " << table.size() << "\n";

    // creating random bombs
    createRandomBombs(40);

    // creating helping numbers
    minecheck();

    // shows number of mines of each square
    for (unsigned i = 0; i < table.size(); i++)
    {
      // turns table into the input source
      table.at(i) = false;
    }
  }

  void Context::createRandomBombs(unsigned initial_click_index)
  {
    std::vector<int> index_v(table.size());
    for (size_t i = 0; i < index_v.size(); ++i)
    {
      index_v[i] = i;
    }

    // making sure squares surrounding initial click place are safe
    // by taking them out of the random index

    // mines bot
    if (initial_click_index < ymax * (xmax - 1))
    {
      // bot right
      if (initial_click_index % xmax != (xmax - 1))
        index_v.erase(index_v.begin() + initial_click_index + xmax + 1);
      // bot
      index_v.erase(index_v.begin() + initial_click_index + xmax);
      // bot left
      if (initial_click_index % xmax != 0)
        index_v.erase(index_v.begin() + initial_click_index + xmax - 1);
    }

    // right
    if ((initial_click_index % xmax) != (xmax - 1))
    {
      index_v.erase(index_v.begin() + initial_click_index + 1);
    }
    // the actual spot
    index_v.erase(index_v.begin() + initial_click_index);
    // left
    if ((initial_click_index % xmax != 0))
    {
      index_v.erase(index_v.begin() + initial_click_index - 1);
    }

    // mines top
    if (initial_click_index >= xmax)
    {
      // top right
      if (initial_click_index % xmax != xmax - 1)
        index_v.erase(index_v.begin() + initial_click_index - xmax + 1);
      // top
      index_v.erase(index_v.begin() + initial_click_index - xmax);
      // top left
      if (initial_click_index % xmax != 0)
        index_v.erase(index_v.begin() + initial_click_index - xmax - 1);
    }

    for (unsigned i = 0; i < minecount; ++i)
    {
      auto random_index = rand() % index_v.size();
      auto index = index_v[random_index];
      index_v.erase(index_v.begin() + random_index);
      warn[index] = 9;
      table.at(index) = true;
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
    // std::cout << "sz: " << table.size() << "\n";

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

  void Context::show()
  {
    for (unsigned i = 0; i < table.size(); i++)
    {
      if (i % xmax == 0)
        std::cout << "\n";

      if (!table.at(i))
      {
        std::cout << ".";
      }
      else
      {
        std::cout << warn.at(i);
      }
    }
    std::cout << "\n";
  }

  void Context::eventcheck(unsigned coord)
  {
    if (warn.at(coord) == 9)
    {
      defeat();
    }
    else
    {
      // this makes it so the selected square is set as already checked
      table[coord] = true;

      // should make the game check the surroudings if it's a spot without mine neighbors
      if (warn.at(coord) == 0)
      {
        // mines top
        if (coord >= xmax)
        {
          // top left
          if (coord % xmax != 0 && !table.at(coord - 1 - xmax))
            eventcheck(coord - 1 - xmax);

          // top
          if (!table.at(coord - xmax))
            eventcheck(coord - xmax);

          // top right
          if (coord % xmax != xmax - 1 && !table.at(coord - 1 - xmax))
            eventcheck(coord + 1 - xmax);
        }

        // left
        if (coord % xmax != 0 && !table.at(coord - 1))
          eventcheck(coord - 1);

        // right
        if ((coord % xmax) != (xmax - 1) && !table.at(coord + 1))
          eventcheck(coord + 1);

        // mines bot
        if (coord < ymax * (xmax - 1))
        {
          // bot left
          if (coord % xmax != 0 && !table.at(coord - 1 + xmax))
            eventcheck(coord - 1 + xmax);
          // bot
          if (!table.at(coord + xmax))
            eventcheck(coord + xmax);
          // bot right
          if (coord % xmax != (xmax - 1) && !table.at(coord + xmax + 1))
            eventcheck(coord + 1 + xmax);
        }
      }
    }
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