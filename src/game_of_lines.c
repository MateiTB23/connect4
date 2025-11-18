#include "game_of_lines.h"

// Implement functions defined in game_of_lines.h

void scanSettings(char *isComputer, int *arenaSize, int *lineLength) {
    char temp;
    printf("Welcome to the connect game\n Do you want to play against another player or AI?\n");
    printf("Play against computer (y/n)>\n");
    scanf("%c", &temp);
    while (true) {
        if (temp == 'y' || temp == 'Y' || temp == 'n' || temp == 'N') {
            *isComputer = temp;
            break;
        } else {
            printf("Invalid input, try again\n");
            scanf("%c", &temp);
        }
    }
    printf("Enter the size of the arena as an integer value n, for n*n arena\n");
    scanf("%d", arenaSize);


    do {
        printf("Enter the length of the line to win the game, it must be an integer smaller than arena size\n");
        scanf("%d", lineLength);
    } while (*lineLength <= 0 || *lineLength > *arenaSize);
}

void scanMove(int *arena, int sizeOfArena, int *moveNumber, char* isComputer) {
    int x;
    int isFound = 0;
    while (isFound == 0) {
        if (*isComputer == 'n' || *isComputer == 'N' || *moveNumber%2==0){
        printf("\nTurn of player %d\nEnter the move you want to play like this: 2, if you want it in colon 2, if colon is full, you will be asked again\n", *moveNumber%2+1);
        scanf("%d", &x);
        } else {
            printf("\n\nTurn of AI\n\n");
            x = rand() % (sizeOfArena);
        }
        // Check if column is full
        if (arena[0 * sizeOfArena + x] != 0) {
            printf("That column is full. Try again.\n");
            continue; // ask for a new column
        }
        for (int i = sizeOfArena - 1; i >= 0; i--) {
            if (arena[i * sizeOfArena + x] == 1 || arena[i * sizeOfArena + x] == 2) {
            } else {
                arena[i * sizeOfArena + x] = *moveNumber%2+1;
                isFound = 1;
                break;
            }
        }
    }
}


int *get_cell(int *arena, int sizeOfArena, int x, int y) {
    return &arena[x * sizeOfArena + y];
}

void updateArena(int *arena, int sizeOfArena, int *moveNumber, char *isComputer) {
    if (*moveNumber % 2 == 0) {
        scanMove(arena, sizeOfArena, moveNumber, isComputer);
        *moveNumber = *moveNumber + 1;
    } else {
        if (*isComputer == 'n' || *isComputer == 'N') {
            scanMove(arena, sizeOfArena, moveNumber, isComputer);
            *moveNumber = *moveNumber + 1;
        } else {
            scanMove(arena, sizeOfArena, moveNumber, isComputer);
            *moveNumber = *moveNumber + 1;
        }
    }

}

void printArena(int *arena, int sizeOfArena) {
    for (int i = 0; i < sizeOfArena; i++) {
        for (int j = 0; j < sizeOfArena; j++)
            printf("%d ", arena[i * sizeOfArena + j]);
        printf("\n");
    }
}

int winner(int *arena, int *sizeOfArena, int *lineLength) {
    //diagonal check for top left to bottom right
    for (int rowStart = 0; rowStart < *sizeOfArena - (*lineLength - 1); rowStart++) {
        int countPlayer = 0;
        int countAI = 0;
        int row, col;
        for (row = rowStart, col = 0; row < *sizeOfArena && col < *sizeOfArena; row++, col++) {
            if (arena[row * (*sizeOfArena) + col] == 1) {
                countPlayer++;
                countAI = 0;
            } else if (arena[row * (*sizeOfArena) + col] == 2) {
                countAI++;
                countPlayer = 0;
            } else {
                countAI = 0;
                countPlayer = 0;
            }
            if (countPlayer == *lineLength) {
                return 1;
            } else if (countAI == *lineLength) {
                return 2;
            }
        }
    }
    for (int colStart = 1; colStart < *sizeOfArena - (*lineLength - 1); colStart++) {
        int countPlayer = 0;
        int countAI = 0;
        int row, col;
        for (col = colStart, row = 0; row < *sizeOfArena && col < *sizeOfArena; row++, col++) {
            if (arena[row * (*sizeOfArena) + col] == 1) {
                countPlayer++;
                countAI = 0;
            } else if (arena[row * (*sizeOfArena) + col] == 2) {
                countAI++;
                countPlayer = 0;
            } else {
                countAI = 0;
                countPlayer = 0;
            }
            if (countPlayer == *lineLength) {
                return 1;
            } else if (countAI == *lineLength) {
                return 2;
            }
        }
    }


    //diagonal check for bottom left to top right
    for (int rowStart = *sizeOfArena - 1; rowStart >= (*lineLength - 1); rowStart--) {
        int countPlayer = 0;
        int countAI = 0;
        int row, col;
        for (row = rowStart, col = 0; row >= 0 && col < *sizeOfArena; row--, col++) {
            if (arena[row * (*sizeOfArena) + col] == 1) {
                countPlayer++;
                countAI = 0;
            } else if (arena[row * (*sizeOfArena) + col] == 2) {
                countAI++;
                countPlayer = 0;
            } else {
                countAI = 0;
                countPlayer = 0;
            }
            if (countPlayer == *lineLength) {
                return 1;
            } else if (countAI == *lineLength) {
                return 2;
            }
        }
    }

    for (int colStart = 1; colStart < *sizeOfArena - (*lineLength - 1); colStart++) {
        int countPlayer = 0;
        int countAI = 0;
        int row, col;
        for (col = colStart, row = *sizeOfArena - 1; row >= 0 && col < *sizeOfArena; row--, col++) {
            if (arena[row * (*sizeOfArena) + col] == 1) {
                countPlayer++;
                countAI = 0;
            } else if (arena[row * (*sizeOfArena) + col] == 2) {
                countAI++;
                countPlayer = 0;
            } else {
                countAI = 0;
                countPlayer = 0;
            }
            if (countPlayer == *lineLength) {
                return 1;
            } else if (countAI == *lineLength) {
                return 2;
            }
        }
    }


    //Horizontal check
    for (int rowStart = 0; rowStart < (*sizeOfArena); rowStart++) {
        int countPlayer = 0;
        int countAI = 0;
        int row, col;
        for (col = 0; col < (*sizeOfArena); col++) {
            if (arena[rowStart * (*sizeOfArena) + col] == 1) {
                countPlayer++;
                countAI = 0;
            } else if (arena[rowStart * (*sizeOfArena) + col] == 2) {
                countAI++;
                countPlayer = 0;
            } else {
                countAI = 0;
                countPlayer = 0;
            }
            if (countPlayer == *lineLength) {
                return 1;
            } else if (countAI == *lineLength) {
                return 2;
            }
        }
    }

    //vertical check
    for (int colStart = 0; colStart < (*sizeOfArena); colStart++) {
        int countPlayer = 0;
        int countAI = 0;
        int row;
        for (row = 0; row < (*sizeOfArena); row++) {
            if (arena[row * (*sizeOfArena) + colStart] == 1) {
                countPlayer++;
                countAI = 0;
            } else if (arena[row * (*sizeOfArena) + colStart] == 2) {
                countAI++;
                countPlayer = 0;
            } else {
                countAI = 0;
                countPlayer = 0;
            }
            if (countPlayer == *lineLength) {
                return 1;
            } else if (countAI == *lineLength) {
                return 2;
            }
        }
    }
    return -1;
}
