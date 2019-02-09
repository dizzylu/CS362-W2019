/*
 * CS362 - Assignment #3
 * Due: 2/10/19
 * Description: Card test for Village
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
    printf("\n\nCard Test: Village\n----------------------------\n\n");

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
    printf("\nPlayer 1 Action Count\nOriginal State: %i\tTest State: %i\n", G.numActions, testG.numActions);

    // Play card
    printf("\nPlay Village Card\n");
    cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);

    // Verify card count increased by one
    int oldCount = G.handCount[0];
    int newCount = testG.handCount[0];
    printf("Card Count\nOriginal State: %i\tTest State: %i\n", oldCount, newCount);
    int result = assertTrue(newCount, oldCount+1);
    if(result)
        printf("Test Passed: One card added to hand\n");
    else if(!result)
        printf("Test Failed: Incorrect number of cards added\n");

    // Verify action count increased by 2
    int oldAct = G.numActions;
    int newAct = testG.numActions;
    printf("\nAction Count\nOriginal State: %i\tTest State: %i\n", oldAct, newAct);
    int res = assertTrue(newAct, oldAct+2);
    if(res)
        printf("Test Passed: Two actions added\n\n\n");
    else if(!res)
        printf("Test Failed: Incorrect number of actions added\n\n\n");

    return 0;
}