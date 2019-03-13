/*
 * CS362 - Assignment #5
 * Due: 3/16/19
 * Description: Card test rewrite for Council Room
 */
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <string.h>

// Tester defined assert
int assertTrue(int test, int expected)
{
    if(test != expected)
        return 0;
    else
        return 1;
}

int main(int argc, char const *argv[])
{
    printf("\n\nCard Test: Council Room\n----------------------------\n\n");

    // Initialize a game to run tests on
    // Source: CS362 card test sample file
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int numPlayers = 2;
    int k[10] = {adventurer, embargo, village, minion, mine,
                 cutpurse, sea_hag, tribute, smithy, council_room};
    int seed = 1000;

    // Use two states to copy and compare
    struct gameState G, testG;
    initializeGame(numPlayers, k, seed, &G);
    memcpy(&testG, &G, sizeof(struct gameState));

    // Display current card count and action count
    printf("Player 1 Hand Count\nOriginal State: %i\tTest State: %i\n", G.handCount[0], testG.handCount[0]);
    printf("\nPlayer 1 Buy Count\nOriginal State: %i\tTest State: %i\n", G.numBuys, testG.numBuys);
    printf("\nPlayer 2 Card Count\nOriginal State: %i\tTest State: %i\n", G.handCount[1], testG.handCount[1]);

    // Play card
    printf("\nPlay Council Room Card\n");
    cardEffect(council_room, choice1, choice2, choice3, &testG, handpos, &bonus);

    // Verify card count increased by 4
    int oldCount = G.handCount[0];
    int newCount = testG.handCount[0];
    printf("Card Count\nOriginal State: %i\tTest State: %i\n", oldCount, newCount);
    int result = assertTrue(newCount, oldCount+4);
    if(result)
        printf("Test Passed: One card added to hand\n");
    else if(!result)
        printf("Test Failed: Incorrect number of cards added\n");

    // Verify buy count increased by 1
    int oldAct = G.numBuys;
    int newAct = testG.numBuys;
    printf("\nBuy Count\nOriginal State: %i\tTest State: %i\n", oldAct, newAct);
    int res = assertTrue(newAct, oldAct+1);
    if(res)
        printf("Test Passed: One action added\n");
    else if(!res)
        printf("Test Failed: Incorrect number of actions added\n");

    // Verify second player drew a card
    int oldDraw = G.handCount[1];
    int newDraw = testG.handCount[1];
    printf("\nSecond player card count\nOriginal: %i\tTest: %i\n", oldDraw, newDraw);
    res = assertTrue(newDraw, oldDraw+1);
    if(res)
        printf("Test Passed: One card added\n\n\n");
    else if(!res)
        printf("Test Failed: Incorrect number of cards added\n\n\n");

    return 0;
}