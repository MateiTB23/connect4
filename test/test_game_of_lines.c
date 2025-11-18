#include "mtest.h"
#include "game_of_lines.h"

// TODO: Write unit tests!

// spiller 1 vinder vandret
TEST_CASE(testSpiller1Horizontalt,
          /* Arrange */
          int sizeOfArena = 4;
          int lineLength = 3;
          int arena[16] = {0}; // 4x4 med alle felter = 0
          // Spiller 1
          // Række 2: (2,0), (2,1), (2,2)
          arena[2 * sizeOfArena + 0] = 1;
          arena[2 * sizeOfArena + 1] = 1;
          arena[2 * sizeOfArena + 2] = 1;

          /* Act */
          int result = winner(arena, &sizeOfArena, &lineLength);

          /* Assert */
          // Forvent at spiller 1 vinder (winner returnerer 1)
          CHECK_EQ_INT(result, 1);
)

//  spiller 1 vinder lodret
TEST_CASE(testSpiller1Vertikalt,
          /* Arrange */
          int sizeOfArena = 4;
          int lineLength = 3;
          int arena[16] = {0}; // 4x4 med alle felter = 0

          arena[0 * sizeOfArena + 1] = 1;
          arena[1 * sizeOfArena + 1] = 1;
          arena[2 * sizeOfArena + 1] = 1;

          /* Act */
          int result = winner(arena, &sizeOfArena, &lineLength);

          /* Assert */
          // Forvent at spiller 1 vinder (winner returnerer 1)
          CHECK_EQ_INT(result, 1);
)

// spiller 1 vinder diagonalt nedad
TEST_CASE(testSpiller1Diagonalt,
          /* Arrange */
          int sizeOfArena = 4;
          int lineLength = 3;
          int arena[16] = {0}; // 4x4 med alle felter = 0

          arena[0 * sizeOfArena + 0] = 1;
          arena[1 * sizeOfArena + 1] = 1;
          arena[2 * sizeOfArena + 2] = 1;

          /* Act */
          int result = winner(arena, &sizeOfArena, &lineLength);

          /* Assert */
          // Forvent at spiller 1 vinder (winner returnerer 1)
          CHECK_EQ_INT(result, 1);
)

// spiller 1 vinder diagonalt nedad
TEST_CASE(testSpiller1DiagonaltOp,
          /* Arrange */
          int sizeOfArena = 4;
          int lineLength = 3;
          int arena[16] = {0}; // 4x4 med alle felter = 0

          arena[0 * sizeOfArena + 2] = 1;
          arena[1 * sizeOfArena + 1] = 1;
          arena[2 * sizeOfArena + 0] = 1;

          /* Act */
          int result = winner(arena, &sizeOfArena, &lineLength);

          /* Assert */
          // Forvent at spiller 1 vinder (winner returnerer 1)
          CHECK_EQ_INT(result, 1);
)

//tester om AI placerer et rigtigt sted med kald af UpdateArena
TEST_CASE(testUpdateArenaAI,

          /* Arrange */
          int size = 4;
          int arena[16] = {0};
          int moveNumber = 1; // AI tur
          char isComputer = 'y';

          srand(0);

          /* Act */
          updateArena(arena, size, &moveNumber, &isComputer);

          /* Assert */
          int countAI = 0;
          int aiColumn = -1;

          // Undersøger nederste række
          for (int col = 0; col < size; col++) {
          if (arena[3 * size + col] == 2) {
          countAI++;
          aiColumn = col;
          }
          }

          // Der må kun være en AI move indtil videre
          CHECK_EQ_INT(countAI, 1);

          // Denne move skal være i en af de gyldige colonner og ikke ved siden af
          CHECK_TRUE(aiColumn >= 0 && aiColumn < size);

          // moveNumber skal være øget korrekt med en, så den bør være 2 nu
          CHECK_EQ_INT(moveNumber, 2);
)


MAIN_RUN_TESTS(testSpiller1Horizontalt, testSpiller1Vertikalt, testSpiller1Diagonalt, testSpiller1DiagonaltOp,
               testUpdateArenaAI)
