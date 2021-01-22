#include <iostream>
#include "context.h"

main()
{
    minesweeper::Context C(difficulty::A);

    C.defeat();

    return 0;
}