/**
 * CS362 - Assignment #4
 * Due: 2/27/19
 * Description: Random test generator for Adventurer card
 */

#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TESTCARD adventurer

int assertTrue(int a, int b)
{
    if(a != b)
        return 0;
    else
        return 1;
}

int main()
{
    printf("\n\nRandom Testing: Adventurer Card\n------------------------------\n\n");

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

        // Mimic card effect on original state
        int drawTreasure = 0, count = 0;
        int temp[MAX_HAND];
        while(drawTreasure < 2)
        {
            if(Game.deckCount[randTurn] < 1)
                shuffle(randTurn, &Game);

            drawCard(randTurn, &Game);
            int cDrawn = Game.hand[randTurn][Game.handCount[randTurn]-1];

            if(cDrawn == copper || cDrawn == silver || cDrawn == gold)
                drawTreasure++;
            else
            {
                temp[count] = cDrawn;
                Game.handCount[randTurn]--;
                count++;
            }
        }

        while(count -1 >= 0)
        {
            Game.discard[randTurn][Game.discardCount[randTurn]++] = temp[count-1];
            count-=1;
        }

        // Compare with original state
        int origTreasure = 0, testTreasure = 0;
        for(int j = 0; j < Game.handCount[randTurn]; ++j)
        {
            if(Game.hand[randTurn][j] == copper || Game.hand[randTurn][j] == silver ||
               Game.hand[randTurn][j] == gold)
            {
                origTreasure++;
            }
        }

        for(int k = 0; k < testG.handCount[randTurn]; ++k)
        {
            if(testG.hand[randTurn][k] == copper || testG.hand[randTurn][k] == silver ||
               testG.hand[randTurn][k] == gold)
            {
                testTreasure++;
            }
        }

        // 2 treasure cards added
        printf("Original Game - Treasure Count: %i\n", origTreasure);
        printf("Test Game - Treasure Count: %i\n", testTreasure);
        res = assertTrue(origTreasure, testTreasure);
        if(!res)
        {
            printf("Test Failed: +2 treasure not added\n\n");
            failed++;
        }
        else if(res)
        {
            printf("Test Passed: +2 treasure added\n\n");
            passed++;
        }

        memset(&Game, 0, sizeof(Game));
        memset(&testG, 0, sizeof(testG));
    }

    printf("\n------------------------------\n");
    printf("Passing Tests: %i\nFailing Tests: %i\nGame Setup Failures: %i\n\n", passed, failed, failedInit);

    return 0;
}