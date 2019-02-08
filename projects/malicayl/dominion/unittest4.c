/*
 * CS362 - Assignment #3
 * Due: 2/10/19
 * Description: Unit test for newGame function
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

int main(int argc, char const *argv[])
{
    printf("\n\nStarting Unit Test 4\n----------------------------\n");

    // Set a gameState ptr to null and verify it's null
    struct gameState* gameTest = NULL;
    printf("Check null game state ptr before creating new game\n");
    if(gameTest)
        printf("Game state ptr is not null - Test Failed\n");
    else if(!gameTest)
        printf("Game state ptr is null - Test Passed\n");

    // Create new game
    gameTest = newGame();

    // Check that gameState ptr now points to new game
    printf("\nCheck game state ptr points to new game\n");
    if(gameTest)
        printf("New game created - Test Passed\n");
    else if(!gameTest)
        printf("New game not created - Test Failed\n");
    printf("\n\n");

    // Prevent memory leaks
    free(gameTest);
    return 0;
}