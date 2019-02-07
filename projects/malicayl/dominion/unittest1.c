/*
 * CS362 - Assignment #3
 * Due: 2/10/19
 * Description: Unit test for getCost function
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

// Test array size
const int arrSize = 10;

int main(int argc, char const *argv[])
{
    printf("\n\nStarting Unit Test #1\n---------------------------\n");

    // Set of cards with correct and incorrect costs
    int testCards[] = {estate, province, silver, adventurer, mine,
                       smithy, village, minion, sea_hag, outpost};
    int testCardCosts[] = {2, 8, 3, 6, 5,
                           4, 3, 5, 4, 5};
    int testWrongCost[] = {6, 5, 5, 9, 0,
                           2, 5, 7, 8, 2};

    // Test cards with correct values
    printf("Testing Card Set with correct values\n");
    for(int i = 0; i < arrSize; i++)
    {
        int result = assertTrue(getCost(testCards[i]), testCardCosts[i]);

        // Display result
        if(result)
            printf("Card #%i: Correct Cost Verified - Test Passed\n", i+1);
        else if(!result)
            printf("Card #%i: Test Failed\n", i+1);
    }

    // Test cards with incorrect values
    printf("\nTesting Card Set with incorrect values\n");
    for(int i = 0; i < arrSize; i++)
    {
        int result = assertTrue(getCost(testCards[i]), testWrongCost[i]);

        // Verify that costs are wrong
        if(!result)
            printf("Card #%i: Incorrect Cost Verified - Test Passed\n", i+1);
        else if(result)
            printf("Card #%i: Test Failed\n", i+1);
    }
    printf("\n\n");

    return 0;
}