#include "game_of_lines.h"

//funktion scanSettings der scanner brugerens settings
void scanSettings(char *isComputer, int *arenaSize, int *lineLength) {
    //midlertidlig variabel
    char temp;
    //brugeren spørges om de vil spille mod en computer eller ej
    printf("Play against computer (y/n)>\n");
    //deres svar gemmes
    scanf("%c", &temp);
    //Hvis inputtet passer, så gemmes den, eller spørges brugeren igen
    while (true) {
        if (temp == 'y' || temp == 'Y' || temp == 'n' || temp == 'N') {
            *isComputer = temp;
            break;
        } else {
            printf("Invalid input, try again\n");
            scanf("%c", &temp);
        }
    }

    //Brugeren bliver spurgt om størrelsen af arenean
    printf("Enter the size of the arena as an integer value n, for n*n arena\n");
    //Størrelse af  arena gemmes i int pointer arenaSize
    scanf("%d", arenaSize);

    //Brugeren spørges om størrelse på linje der skal vinde spillet, som gemmes i pointer lineLength, hvis ikke større end 0 og <= arena størrelse, så spørges bruger igen
    do {
        printf("Enter the length of the line to win the game, it must be an integer smaller than arena size\n");
        scanf("%d", lineLength);
    } while (*lineLength <= 0 || *lineLength > *arenaSize);
}

//funktion scanmove, til at beregne brugeren eller AI næste move
void scanMove(int *arena, int sizeOfArena, int *moveNumber, char* isComputer) {
    //variabler x og isFound til lokation i array og om movet kan spilles
    int x;
    bool isFound = false;
    //mens isFound er falsk
    while (isFound == false) {
        //tjek hvis det er en bruger der skal spille
        if (*isComputer == 'n' || *isComputer == 'N' || *moveNumber%2==0){
            //hvis det er brugeren, så bliver bruger promptet til at skrive deres move, som gemmes i x
        printf("\nTurn of player %d\nEnter the move you want to play like this: 2, if you want it in colon 2, if colon is full, you will be asked again\n", *moveNumber%2+1);
        scanf("%d", &x);
            //ellers hvis det ikke er spilleren
        } else {
            //så må det være AI tur, og dens move beregnes ved hjælp af rand og arenastørrelsen
            printf("\n\nTurn of AI\n\n");
            x = rand() % (sizeOfArena);
        }
        // Check hvis colonne er fuld
        if (arena[0 * sizeOfArena + x] != 0) {
            printf("That column is full. Try again.\n");
            continue; // spørger efter ny colonne
        }
        //Check hvis at colonnen hvor brugeren vil ligge en cirkel er udfyldt
        for (int i = sizeOfArena - 1; i >= 0; i--) {
            //hvis udfyldt sker der ikke noget
            if (arena[i * sizeOfArena + x] == 1 || arena[i * sizeOfArena + x] == 2) {
                //hvis ikke udfyldt, så ligges 1 hvis det er bruger move på pladsen, eller 2 hvis bruger 2 eller AI
            } else {
                arena[i * sizeOfArena + x] = *moveNumber%2+1;
                //isFound sættes til sand
                isFound = true;
                break;
            }
        }
    }
}

//funktion updateArena, som opdaterer arenaen baseret på nyeste move
void updateArena(int *arena, int sizeOfArena, int *moveNumber, char *isComputer) {
    scanMove(arena, sizeOfArena, moveNumber, isComputer);
    (*moveNumber)++;
}

//Funktion printArena, som looper igennem arena og printer den
void printArena(int *arena, int sizeOfArena) {
    for (int i = 0; i < sizeOfArena; i++) {
        for (int j = 0; j < sizeOfArena; j++)
            printf("%d ", arena[i * sizeOfArena + j]);
        printf("\n");
    }
}

//Funktion winner, som scanner hvis der er en vinder, og returnerer en værdi baseret på hvem det er
int winner(int *arena, int *sizeOfArena, int *lineLength) {
    //I hele funktionen bliver der returneret 1 hvis spiller 1 vinder, 2 hvis spiller 2 eller AI vinder og 0 hvis uafgjort, -1 ellers

    //diagonal check fra venstre top til højre bund
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


    //diagonal check fra bund venstre til højre top
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


    //Horizontalt check
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

    //Vertikalt check
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
    // check for uafgjort
    int full = 1;
    for (int i = 0; i < (*sizeOfArena) * (*sizeOfArena); i++) {
        if (arena[i] == 0) {   // 0 er tom i din nuværende repræsentation
            full = 0;
            break;
        }
    }
    if (full) {
        return 0;   // uafgjort
    }
    return -1;
}
