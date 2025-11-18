#include <stdio.h>
#include <stdlib.h>
#include "game_of_lines.h"


void game_of_lines(char isComputer, int arenaSize, int sizeOfWinLine);

int main(void) {
    srand(time(NULL));
    char isComputer;
    int arenaSize;
    int sizeOfWinLine;
    scanSettings(&isComputer, &arenaSize, &sizeOfWinLine);
    game_of_lines(isComputer, arenaSize, sizeOfWinLine);

    return 0;
}

void game_of_lines(char isComputer, int arenaSize, int sizeOfWinLine) {
    // Create an arena (e.g. use HINT 1)
    int *arena = (int *) malloc(sizeof(int) * arenaSize * arenaSize); // the arena is quadratic, i.e.
    for (int i = 0; i < arenaSize * arenaSize; i++) {
        arena[i] = 0;
    }

    int moveNumber = 0; // Who should perform the next move: Player 0 or Player/Computer 1?
    printArena(arena, arenaSize);


    int theWinner = -1;
    do {
        updateArena(arena, arenaSize, &moveNumber, &isComputer);
        printArena(arena, arenaSize);

        theWinner = winner(arena, &arenaSize, &sizeOfWinLine);
    } while (theWinner == -1);

    if (theWinner == 0) {
        printf("The game is a draw\n");
    } else if (theWinner == 1) {
        printf("The player 1 has won\n");
    } else if (theWinner == 2 && (isComputer == 'n' || isComputer == 'N')) {
        printf("The player 2 has won\n");
    } else {
        printf("The AI has won\n");
    }
}
