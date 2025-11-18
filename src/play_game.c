#include <stdio.h>
#include <stdlib.h>
#include "game_of_lines.h"


int main(void) {
    //random bliver seedet til tid 0
    srand(time(NULL));
    //variabler til om det er spiller eller computer, arena størrelse og størrelse på linje der vinder
    char isComputer;
    int arenaSize;
    int sizeOfWinLine;
    //scanSettings kalde for at vide brugerens indstillinger, som gemmes i tidligere nævnte variabler
    scanSettings(&isComputer, &arenaSize, &sizeOfWinLine);
    //gameOfLines kaldes med argumenter isComputer, arenaSize og sizeOfWinLine
    gameOfLines(isComputer, arenaSize, sizeOfWinLine);

    //return 0 fordi programmet er slut
    return 0;
}

void gameOfLines(char isComputer, int arenaSize, int sizeOfWinLine) {
    // Arena laves via malloc
    int *arena = (int *) malloc(sizeof(int) * arenaSize * arenaSize);
    //Arena udfyldes med 0, valgte 0 fremfor _ da jeg synes det lignede mere den tomme bane i det rigtige spil
    for (int i = 0; i < arenaSize * arenaSize; i++) {
        arena[i] = 0;
    }

    //moveNumber initialiseres til 0, og det er en variabel til at holde styr på hvem der skal spille
    int moveNumber = 0;

    //printArena kaldes, med argumenterne selve arena og arenaStørrelse
    printArena(arena, arenaSize);


    //variabel theWinner sættes til -1
    int theWinner = -1;
    do {
        //mens theWinner er -1, så kaldes updateArena, printArena og winner, hvor winners resultat gemmes i variabel theWinner. Hvis der bliver fundet en vinder eller uafgjort stopper løkken dermed
        updateArena(arena, arenaSize, &moveNumber, &isComputer);
        printArena(arena, arenaSize);

        theWinner = winner(arena, &arenaSize, &sizeOfWinLine);
    } while (theWinner == -1);

    //Hvis vinderen er 0, så er kampen uafgjort
    if (theWinner == 0) {
        printf("The game is a draw\n");
        //Hvis vinderen er 1, så har spiller 1 vundet
    } else if (theWinner == 1) {
        printf("The player 1 has won\n");
        //Hvis vinder er 2 og det ikke er computer, så har spillet 2 vundet
    } else if (theWinner == 2 && (isComputer == 'n' || isComputer == 'N')) {
        printf("The player 2 has won\n");
    } else {
        // Ellers har AI vundet
        printf("The AI has won\n");
    }
}
