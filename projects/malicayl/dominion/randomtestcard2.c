/**
 * CS362 - Assignment #4
 * Due: 2/27/19
 * Description: Random test generator for Smithy card
 */

#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TESTCARD smithy

int assertTrue(int a, int b)
{
    if(a != b)
        return 0;
    else
        return 1;
}

int main()
{
    printf("\n\nRandom Testing: Smithy Card\n------------------------------\n\n");

    // Set game parameters
    // Source: CS362 card test sample
    srand(time(NULL));
    const int numTests = 100;
    struct gameState Game, testG;
    int k[10] = {adventurer, embargo, village, minion, mine,
                 cutpurse, sea_hag, tribute, smithy, council_room};
    int seed = 1000, passed = 0, failed = 0, failedInit = 0, res = 0,
        maxPlay = 4, minPlay = 2;

    // Run tests
    for(int i = 0; i < numTests; ++i)
    {
        printf("Test #%i\n", i+1);

        // Randomize number of players and player turn
        int numPlayers = rand() % (maxPlay - minPlay + 1) + minPlay,
            randTurn = rand() % numPlayers;

        // Setup a game and copy state to make comparisons
        int setup = initializeGame(numPlayers, k, seed, &Game);
        if(setup == -1)
        {
            printf("*Game Initialization Failed*\n");
            failedInit++;
        }
        Game.whoseTurn = randTurn;
        memcpy(&testG, &Game, sizeof(struct gameState));

        // Randomize choices and play card
        int choice1 = rand(), choice2 = rand(), choice3 = rand(), bonus = rand();
        cardEffect(TESTCARD, choice1, choice2, choice3, &testG, 0, &bonus);

        // Mimic smithy card
        for(int j = 0; j < 3; ++j)
            drawCard(randTurn, &Game);
        discardCard(0, randTurn, &Game, 0);

        // Compare with original state
        int origHand = Game.handCount[randTurn], testHand = testG.handCount[randTurn];

        // 3 cards added to hand
        printf("Original Game - Hand Count: %i\n", origHand);
        printf("Test Game - Hand Count: %i\n", testHand);
        res = assertTrue(origHand, testHand);
        if(!res)
        {
            printf("Test Failed: +1 card not added\n\n");
            failed++;
        }
        else if(res)
        {
            printf("Test Passed: +1 card added\n\n");
            passed++;
        }

        memset(&Game, 0, sizeof(Game));
        memset(&testG, 0, sizeof(testG));
    }

    // Display results
    printf("\n------------------------------\n");
    printf("Passing Tests: %i\nFailing Tests: %i\nGame Setup Failures: %i\n\n", passed, failed, failedInit);

    return 0;
}