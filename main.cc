#include <iostream>
#include "context.h"

main()
{
    unsigned i, j;


    std::cout << "Welcome to minesweeper!\nInput you first move to start the game:\nthe x position you want: ";
    std::cin >> i;
    std::cout << "\nthe y position you want to check: ";
    std::cin >> j;

    minesweeper::Context C(difficulty::A);

    C.show();

    return 0;
}