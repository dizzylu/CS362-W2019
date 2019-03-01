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
    printf("\nRandom Testing: Smithy Card\n------------------------------\n\n");

    // Set game parameters
    // Source: CS362 card test sample
    srand(time(NULL));
    const int numTests = 100;
    struct gameState Game, testG;
    int k[10] = {adventurer, embargo, village, minion, mine,
                 cutpurse, sea_hag, tribute, smithy, council_room};
    int seed = 1000, passed = 0, failed = 0, failedInit = 0, res = 0,
        maxPlay = 4, minPlay = 2, handPosCard = 0;

    for(int i = 0; i < numTests; ++i)
    {
        // Randomize number of players and player turn
        printf("***Test #%i***\n", i+1);
        int numPlayers = rand() % (maxPlay - minPlay + 1) + minPlay,
            randTurn = rand() % numPlayers;

        // Setup a game and copy state to make comparisons
        int setup = initializeGame(numPlayers, k, seed, &Game);
        if(setup == -1)
        {
            printf("*Game Initialization Failed*\n");
            failedInit++;
        }

        // Randomize values then play card
        Game.deckCount[randTurn] = rand() % MAX_DECK;
        Game.discardCount[randTurn] = rand() % MAX_DECK;
        Game.handCount[randTurn] = rand() % MAX_HAND;
        Game.whoseTurn = randTurn;
        Game.numActions = rand() % 50;
        Game.hand[randTurn][handPosCard] = smithy;
        memcpy(&testG, &Game, sizeof(struct gameState));

        printf("Initial Values\n");
        printf("Hand Count - Original: %i\tTest: %i\n\n", Game.handCount[randTurn], testG.handCount[randTurn]);

        // Randomize choices and play card
        int choice1 = rand(), choice2 = rand(), choice3 = rand(), bonus = rand();
        cardEffect(TESTCARD, choice1, choice2, choice3, &testG, handPosCard, &bonus);

        // Mimic smithy card
        for(int j = 0; j < 3; ++j)
            drawCard(randTurn, &Game);
        discardCard(handPosCard, randTurn, &Game, 0);

        // Compare with original state
        int origHand = Game.handCount[randTurn], testHand = testG.handCount[randTurn];

        // 3 cards added to hand
        printf("Result: +3 Cards and discard\n");
        printf("Original Game - Hand Count: %i\n", origHand);
        printf("Test Game - Hand Count: %i\n", testHand);
        res = assertTrue(origHand, testHand);
        if(!res)
        {
            printf("Test Failed: +3 cards not added\n\n");
            failed++;
        }
        else if(res)
        {
            printf("Test Passed: +3 cards added\n\n");
            passed++;
        }

        memset(&Game, 0, sizeof(Game));
        memset(&testG, 0, sizeof(testG));
    }

    printf("\n------------------------------\n");
    printf("Passing Tests: %i\nFailing Tests: %i\nGame Setup Failures: %i\n\n", passed, failed, failedInit);

    return 0;
}