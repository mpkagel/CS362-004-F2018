#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
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
	struct gameState g;
	int seed = 5;
	int numPlayers = 2;
	int result = 1;
	char message[512];

	initializeGame(numPlayers, k, seed, &g);

	printf("-----  Testing supplyCount  -----\n");
	
	int supply = supplyCount(adventurer, &g);

	// supply should be 10
	sprintf(message, "FAIL: supply should be 10");
	assertEquality(supply, 10, message, &result);

	if (result) {
		printf("\n+++++ : PASS, unittest1 passed.\n");
	} else {
		printf("\n+++++ : FAIL, unittest1 failed.\n");
	}

	return 0;

}
