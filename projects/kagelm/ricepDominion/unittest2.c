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
	//int thisPlayer = 0;
	int numPlayers = 2;
	int result = 1;
	char message[512];

	initializeGame(numPlayers, k, seed, &g);

	printf("-----  Testing handCard  -----\n");
	
	int card = handCard(1, &g);
	int currentPlayer = whoseTurn(&g);	

	// With a seed of 5, the card in position 1 should be 1 for Estate
	sprintf(message, "FAIL: handCard card position should be 1 for Estate\n");	
	assertEquality(card, 1, message, &result);
	// The next assert is to check if the correct player was used
	sprintf(message, "FAIL: handCard player should be 0\n");	
	assertEquality(currentPlayer, 0, message, &result);


	if (result) {
		printf("\n+++++ : PASS, unittest2 passed.\n");
	} else {
		printf("\n+++++ : FAIL, unittest2 failed.\n");
	}

	return 0;

}
