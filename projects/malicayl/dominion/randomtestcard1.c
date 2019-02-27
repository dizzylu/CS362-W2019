/**
 * CS362 - Assignment #4
 * Due: 2/27/19
 * Description: Random test generator for Village card
 */

#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const int numTests = 100;

// Tester defined assert
int assertTrue(int a, int b)
{
    if(a != b)
        return 0;
    else
        return 1;
}

int main()
{
    srand(time(NULL));
    printf("\n\nRandom Testing: Village Card\n------------------------------\n\n");

    // Set game parameters
    // Source: CS362 Card Test sample
    struct gameState Game, testG;
    int k[10] = {adventurer, embargo, village, minion, mine,
                 cutpurse, sea_hag, tribute, smithy, council_room};

    // Run tests
    int passed = 0, failed = 0, failedInit = 0, res;
    for(int i = 0; i < numTests; ++i)
    {
        // Set up a game and copy state to make comparisons
        printf("Test #%i\n", i+1);
        int numPlayers = rand() % MAX_PLAYERS + 1;
        int seed = rand() % 1000;
        int setup = initializeGame(numPlayers, k, seed, &Game);
        if(setup == -1)
        {
            printf("*Game Initialization Failed*\n");
            failedInit++;
        }
        memcpy(&testG, &Game, sizeof(struct gameState));

        // Randomize choices and play card
        int choice1 = rand() % 3 + 1, choice2 = rand() % 3 + 1, choice3 = rand() % 3 + 1, bonus = 0;
        cardEffect(village, choice1, choice2, choice3, &testG, 0, &bonus);

        // Compare with original state
        int playerTurn = whoseTurn(&Game),
            origCount = Game.deckCount[playerTurn],
            testCount = testG.deckCount[playerTurn],
            origAct = Game.numActions,
            testAct = testG.numActions;

        printf("Original Game - Deck Count: %i\n", origCount);
        printf("Test Game - Deck Count: %i\n", testCount);
        res = assertTrue(origCount-1, testCount);
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

        // Check number of actions
        printf("Original Game - Action Count: %i\n", origAct);
        printf("Test Game - Action Count: %i\n", testAct);
        res = assertTrue(origAct+2, testAct);
        if(!res)
        {
            printf("Test Failed: +2 actions not added\n\n");
            failed++;
        }
        else if(res)
        {
            printf("Test Passed: +2 actions added\n\n");
            passed++;
        }

        // Clear game states
        memset(&Game, 0, sizeof(Game));
        memset(&testG, 0, sizeof(testG));
    }

    printf("\n------------------------------\n");
    printf("Passing Tests: %i\nFailing Tests: %i\nGame Setup Failures: %i\n\n", passed, failed, failedInit);

    return 0;
}