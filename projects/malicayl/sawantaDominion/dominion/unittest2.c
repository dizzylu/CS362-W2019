/*
 * CS362 - Assignment #5
 * Due: 3/16/19
 * Description: Unit test for kingdomCards function
 */
#include "dominion_helpers.h"
#include <stdio.h>

// Tester defined assert
int assertTrue(int test, int expected)
{
    if(test != expected)
        return 0;
    else
        return 1;
}

// Reference to cards being used in test
const int cardRef[] = {adventurer, council_room, feast, gardens, mine,
                       remodel, smithy, village, minion, steward};

int main(int argc, char const *argv[])
{
    printf("\n\nStarting Unit Test 2\n--------------------------\n");

    // Initialize a set of kingdom cards
    int* testKingdomCards = kingdomCards(cardRef[0], cardRef[1], cardRef[2], cardRef[3], cardRef[4],
                                         cardRef[5], cardRef[6], cardRef[7], cardRef[8], cardRef[9]);

    // Verify cards were placed in the correct order
    printf("Verify cards are in correct order\n");
    for(int i = 0; i < 10; i++)
    {
        int result = assertTrue(testKingdomCards[i], cardRef[i]);

        if(result)
            printf("Card #%i: Correct Card - Test Passed\n", i+1);
        else if(!result)
            printf("Card #%i: Incorrect Card - Test Failed\n", i+1);
    }
    printf("\n");

    // Choose single card and compare with the test set
    printf("Verify third card is the only match in the set\n");
    for(int i = 0; i < 10; i++)
    {
        int result = assertTrue(testKingdomCards[i], cardRef[2]);
        if(result)
            printf("Card #%i: Correct Card - Test Passed\n", i+1);
        else if(!result)
            printf("Card #%i: Incorrect Card - Test Failed\n", i+1);
    }

    printf("\nVerify fifth card is the only match in the set\n");
    for(int i = 0; i < 10; i++)
    {
        int result = assertTrue(testKingdomCards[i], cardRef[4]);
        if(result)
            printf("Card #%i: Correct Card - Test Passed\n", i+1);
        else if(!result)
            printf("Card #%i: Incorrect Card - Test Failed\n", i+1);
    }

    printf("\nVerify ninth card is the only match in the set\n");
    for(int i = 0; i < 10; i++)
    {
        int result = assertTrue(testKingdomCards[i], cardRef[8]);
        if(result)
            printf("Card #%i: Correct Card - Test Passed\n", i+1);
        else if(!result)
            printf("Card #%i: Incorrect Card - Test Failed\n", i+1);
    }
    printf("\n\n");

    // Prevent memory leak
    free(testKingdomCards);
    testKingdomCards = NULL;

    return 0;
}