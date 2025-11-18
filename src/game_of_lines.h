#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Define function prototypes, (and new datatypes if you need it).
void scanSettings(char *isComputer, int *arenaSize, int *lineLength);

void scanMove(int *arena, int sizeOfArena, int *moveNumber, char *isComputer);

int *get_cell(int *arena, int sizeOfArena, int x, int y);

void updateArena(int *arena, int sizeOfArena, int *moveNumber, char *isComputer);

void printArena(int *arena, int sizeOfArena);

int winner(int *arena, int *sizeOfArena, int *lineLength);