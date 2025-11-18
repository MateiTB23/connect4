#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

//Prototype til funktion scanSettings som scanner de indstillinger brugeren vil have til spillet
void scanSettings(char *isComputer, int *arenaSize, int *lineLength);

//Prototype til funktion scanMove der scanner det næste move for bruger eller AI
void scanMove(int *arena, int sizeOfArena, int *moveNumber, char *isComputer);

//Funktion updateArena der opdaterer arenaen efter hvert move
void updateArena(int *arena, int sizeOfArena, int *moveNumber, char *isComputer);

//Funktion printArena der printer arenean efter hvert move
void printArena(int *arena, int sizeOfArena);

//Funktion winner som returnerer hvem vinderen er når der er en vinder
int winner(int *arena, int *sizeOfArena, int *lineLength);

//Prototype til funktion gameOfLines der kalder de andre funktioner
void gameOfLines(char isComputer, int arenaSize, int sizeOfWinLine);