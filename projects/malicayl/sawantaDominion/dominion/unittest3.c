/*
 * CS362 - Assignment #5
 * Due: 3/16/19
 * Description: Unit test for whoseTurn function
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

// Declare specific number of player to test
const int testPlayers = 8;

int main(int argc, char const *argv[])
{
    // Set game state starting at first player
    printf("\n\nStarting Unit Test 3\n--------------------------\n\n");
    struct gameState* testG = malloc(sizeof(struct gameState));
    testG->whoseTurn = 0;

    // Update player and confirm correct turn
    printf("Verify correct player and update turn status\n");
    for(int i = 0; i < testPlayers; i++)
    {
        int turnFunc = whoseTurn(testG);
        int actualVal = testG->whoseTurn;

        // Display Results
        printf("Actual Player Turn: P%i, Turn Function Result: P%i, Check Player: P%i\t", actualVal, turnFunc, i);
        int result = assertTrue(turnFunc, i);
        if(result)
            printf("Test Passed\n");
        else if(!result)
            printf("Test Failed\n");

        // Update player turn
        testG->whoseTurn += 1;
    }

    // Set player turn to P3 and iterate over every player to confirm turn
    testG->whoseTurn = 3;
    printf("\nVerify that P3 has the current turn only\n");
    for(int i = 0; i < testPlayers; i++)
    {
        int turnFunc = whoseTurn(testG);
        int actualVal = testG->whoseTurn;

        // Display Results
        printf("Actual Player Turn: P%i, Turn Function Result: P%i, Check Player: P%i\t", actualVal, turnFunc, i);
        int result = assertTrue(i, turnFunc);
        if(result)
            printf("Test Passed\n");
        else if(!result)
            printf("Test Failed\n");
    }

    // Set player turn to P5 and iterate over every player to confirm turn
    testG->whoseTurn = 5;
    printf("\nVerify that P5 has the current turn only\n");
    for(int i = 0; i < testPlayers; i++)
    {
        int turnFunc = whoseTurn(testG);
        int actualVal = testG->whoseTurn;

        // Display Results
        printf("Actual Player Turn: P%i, Turn Function Result: P%i, Check Player: P%i\t", actualVal, turnFunc, i);
        int result = assertTrue(i, turnFunc);
        if(result)
            printf("Test Passed\n");
        else if(!result)
            printf("Test Failed\n");
    }

    // Set player turn to P7 and iterate over every player to confirm turn
    testG->whoseTurn = 7;
    printf("\nVerify that P7 has the current turn only\n");
    for(int i = 0; i < testPlayers; i++)
    {
        int turnFunc = whoseTurn(testG);
        int actualVal = testG->whoseTurn;

        // Display Results
        printf("Actual Player Turn: P%i, Turn Function Result: P%i, Check Player: P%i\t", actualVal, turnFunc, i);
        int result = assertTrue(i, turnFunc);
        if(result)
            printf("Test Passed\n");
        else if(!result)
            printf("Test Failed\n");
    }

    // Set player turn to non existant player and make sure no one has a turn
    testG->whoseTurn = 65;
    printf("\nVerify that no one has the current turn\n");
    for(int i = 0; i < testPlayers; i++)
    {
        int turnFunc = whoseTurn(testG);
        int actualVal = testG->whoseTurn;

        // Display Results
        printf("Actual Player Turn: P%i, Turn Function Result: P%i, Check Player: P%i\t", actualVal, turnFunc, i);
        int result = assertTrue(i, turnFunc);
        if(result)
            printf("Test Passed\n");
        else if(!result)
            printf("Test Failed\n");
    }
    printf("\n\n");

    // Prevent memory leaks
    free(testG);
    testG = NULL;
    return 0;
}