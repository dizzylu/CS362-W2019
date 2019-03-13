/*
 * CS362 - Assignment #5
 * Due: 3/16/19
 * Description: Card test for Smithy
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
    printf("\n\nCard Test: Smithy\n----------------------------\n\n");

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

    // Display current count of both states
    printf("Player 1 Hand Count\nOriginal State: %i\tTest State: %i\n", G.handCount[0], testG.handCount[0]);

    // Test that current player drew 3 cards and discarded current card
    printf("\nPlay Smithy card\n");
    cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
    int oldCount = G.handCount[0];
    int newCount = testG.handCount[0];
    printf("Original State: %i\tTest State: %i\n", oldCount, newCount);

    int result = assertTrue(newCount, oldCount+2);
    if(result)
        printf("\nTest Passed: 3 cards added and 1 card discarded\n\n\n");
    else if(!result)
        printf("\nTest Failed: Incorrect amount of cards added to deck\n\n\n");

    return 0;
}