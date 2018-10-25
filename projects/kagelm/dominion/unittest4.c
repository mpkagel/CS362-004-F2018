#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

void assertEquality(int a, int b, char* message, int* result) {
	if (a != b) {
		printf(message);
		*result = 0;
	}
}

int main() {
	int k[10] = { adventurer, gardens, embargo, village, minion,
					mine, cutpurse, sea_hag, tribute, smithy };
	struct gameState g, testg;
	int seed = 5;
	//int thisPlayer = 0;
	int numPlayers = 2;
	int result = 1;
	char message[512];
	
	initializeGame(numPlayers, k, seed, &testg);

	printf("-----  Testing isGameOver  -----\n");

	// Test 1 tests province condition for ending game
	memcpy(&g, &testg, sizeof(struct gameState));
	g.supplyCount[province] = 0;
	int outcome = isGameOver(&g);
	sprintf(message, "FAIL: Test 1 isGameOver outcome should be 1\n");
	assertEquality(outcome, 1, message, &result);
	if (!result) {
		printf("TEST1 failed\n");
	}

	// Test 2 tests supply condition for ending game
	memcpy(&g, &testg, sizeof(struct gameState));
	g.supplyCount[copper] = 0;
	g.supplyCount[silver] = 0;
	g.supplyCount[gold] = 0;
	outcome = isGameOver(&g);
	sprintf(message, "FAIL: Test 2 isGameOver outcome should be 1\n");
	assertEquality(outcome, 1, message, &result);
	if (!result) {
		printf("TEST2 failed\n");
	}

	// Test 3 tests when the game hasn't actually ended yet
	memcpy(&g, &testg, sizeof(struct gameState));
	outcome = isGameOver(&g);
	sprintf(message, "FAIL: Test 3 isGameOver outcome should be 0\n");
	assertEquality(outcome, 0, message, &result);
	if (!result) {
		printf("TEST3 failed\n");
	}

	if (result) {
		printf("\n+++++ : PASS, unittest4 passed.\n");
	} else {
		printf("\n+++++ : FAIL, unittest4 failed.\n");	
	}

	return 0;
}

