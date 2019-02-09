/*
 * CS362 - Assignment #3
 * Due: 2/10/19
 * Description: Card test for Adventurer
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
    printf("\n\nCard Test: Adventurer\n----------------------------\n\n");

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

    // Play adventurer card on test state
    printf("\nPlay Adventurer card\n");
    cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

    // Verify if card count increased by two
    printf("Original State: %i\tTest State: %i\n", G.handCount[0], testG.handCount[0]);
    int result = assertTrue(testG.handCount[0], G.handCount[0]+2);
    if(result)
        printf("Test Passed: 2 cards to deck\n");
    else if(!result)
        printf("Test Failed: Incorrect amount of cards added to deck\n");

    // Verify that two treasure cards were added
    int oldTreasureCt = 0, newTreasureCt = 0;
    for(int i = 0; i < G.handCount[0]; i++)
    {
        if(G.hand[0][i] == copper || G.hand[0][i] == silver || G.hand[0][i] == gold)
            oldTreasureCt += 1;
    }
    for(int i = 0; i < testG.handCount[0]; i++)
    {
        if(testG.hand[0][i] == copper || testG.hand[0][i] == silver || testG.hand[0][i] == gold)
            newTreasureCt += 1;
    }
    printf("\nVerify that the two cards added are treasure cards\n");
    printf("Old treasure count: %i\tNew treasure count: %i\n", oldTreasureCt, newTreasureCt);

    int res = assertTrue(newTreasureCt, oldTreasureCt+2);
    if(res)
        printf("Test Passed: 2 treasure cards added\n\n");
    else if(!res)
        printf("Test Failed: Cards added are not both treasure cards\n\n");

    return 0;
}