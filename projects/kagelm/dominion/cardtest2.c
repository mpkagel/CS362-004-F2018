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

int compareGameStateTest1(int numPlayers, struct gameState g, struct gameState testg) {
	int i, j;
	int result = 1;	
	char message[512];
	char functionName[256] = "compareGameStateTest1";

	// *************** Compare gameStates ***************
	// numPlayers
	sprintf(message, "FAILED: %s numPlayers\n", functionName);
	assertEquality(g.numPlayers, testg.numPlayers, message, &result);
	// supplyCount
	for (i = 0; i < treasure_map + 1; i++) {
		sprintf(message, "FAILED: %s supplyCount card %d\n", functionName, i);
		assertEquality(g.supplyCount[i], testg.supplyCount[i], message, &result);
	}
	// embargoTokens
	for (i = 0; i < treasure_map + 1; i++) {
		sprintf(message, "FAILED: %s embargoTokens card %d\n", functionName, i);
		assertEquality(g.embargoTokens[i], testg.embargoTokens[i], message, &result);
	}
	// outpostPlayed
	sprintf(message, "FAILED: %s outpostPlayed\n", functionName);
	assertEquality(g.outpostPlayed, testg.outpostPlayed, message, &result);
	// outpostTurn
	sprintf(message, "FAILED: %s outpostTurn\n", functionName);
	assertEquality(g.outpostTurn, testg.outpostTurn, message, &result);
	// whoseTurn
	sprintf(message, "FAILED: %s whoseTurn\n", functionName);
	assertEquality(g.whoseTurn, testg.whoseTurn, message, &result);
	// phase
	sprintf(message, "FAILED: %s phase\n", functionName);
	assertEquality(g.phase, testg.phase, message, &result);
	// numActions
	sprintf(message, "FAILED: %s numActions\n", functionName);
	assertEquality(g.numActions, testg.numActions - 1, message, &result);
	// coins
	sprintf(message, "FAILED: %s coins\n", functionName);	
	assertEquality(g.coins, testg.coins + 1, message, &result);
	// numBuys
	sprintf(message, "FAILED: %s numBuys\n", functionName);	
	assertEquality(g.numBuys, testg.numBuys, message, &result);
	// hand
	for (i = 0; i < numPlayers; i++) {
		for (j = 0; j < MAX_HAND; j++) {
			if (i == 0 && j == 0) {
				sprintf(message, "FAILED: %s hand player %d, pos %d\n", functionName, i, j);			
				assertEquality(g.hand[i][j], 4, message, &result);                 			
			} else if (i == 0 && j == 5){ 
				sprintf(message, "FAILED: %s hand player %d, pos %d\n", functionName, i, j);			
				assertEquality(g.hand[i][j], 4, message, &result);                 			
			} else {
				sprintf(message, "FAILED: %s hand player %d, pos %d\n", functionName, i, j);			
				assertEquality(g.hand[i][j], testg.hand[i][j], message, &result);
			}
		}
	}	
	// handCount
	for (i = 0; i < numPlayers; i++) {
		if (i == 0) {
			sprintf(message, "FAILED: %s handCount %d\n", functionName, i);			
			assertEquality(g.handCount[i], 6, message, &result); 
		} else {
			sprintf(message, "FAILED: %s handCount %d\n", functionName, i);			
			assertEquality(g.handCount[i], testg.handCount[i], message, &result); 
		}
	}		
	// deck
	for (i = 0; i < numPlayers; i++) {
		for (j = 0; j < MAX_DECK; j++) {
			sprintf(message, "FAILED: %s deck player %d, pos %d\n", functionName, i, j);			
			assertEquality(g.deck[i][j], testg.deck[i][j], message, &result);
		}
	}
	// deckCount
	for (i = 0; i < numPlayers; i++) {
		if (i == 0) {
			sprintf(message, "FAILED: %s deckCount %d\n", functionName, i);			 		
  		assertEquality(g.deckCount[i], 3, message, &result); 
		} else {
			sprintf(message, "FAILED: %s deckCount %d\n", functionName, i);			
			assertEquality(g.deckCount[i], testg.deckCount[i], message, &result); 
		}
	}
	// discard
	for (i = 0; i < numPlayers; i++) {
		for (j = 0; j < 100; j++) {
			sprintf(message, "FAILED: %s discard player %d, pos %d\n", functionName, i, j);					
			assertEquality(g.discard[i][j], testg.discard[i][j], message, &result);
		}
	}
	// discardCount
	for (i = 0; i < numPlayers; i++) {
		sprintf(message, "FAILED: %s discardCount %d\n", functionName, i);			
		assertEquality(g.discardCount[i], testg.discardCount[i], message, &result);
	}
	// playedCards
	for (i = 0; i < 100; i++) {
		if (i == 0) {
			sprintf(message, "FAILED: %s playedCards %d\n", functionName, i);			
 			assertEquality(g.playedCards[i], 7, message, &result); 
		} else {
			sprintf(message, "FAILED: %s playedCards %d\n", functionName, i);			
 			assertEquality(g.playedCards[i], testg.playedCards[i], message, &result); 
		}
	}
	// playedCardCount
	sprintf(message, "FAILED: %s playedCardCount\n", functionName);	
	assertEquality(g.playedCardCount, 1, message, &result);

	return result;

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

	printf("-----  Testing Adventurer card  -----\n");

	// Test 1 
	memcpy(&g, &testg, sizeof(struct gameState));
	g.hand[0][0] = adventurer;
	int outcome = playCard(0, 0, 0, 0, &g);
	sprintf(message, "FAIL: Test 1 Adventurer card outcome should be 0\n");
	assertEquality(outcome, 0, message, &result);
	// compareGameStateTest1 
	result = compareGameStateTest1(numPlayers, g, testg);
	if (!result) {
		printf("TEST1 failed\n");
	}

	if (result) {
		printf("\n+++++ : PASS, cardtest2 passed.\n");
	} else {
		printf("\n+++++ : FAIL, cardtest2 failed.\n");	
	}

	return 0;
}

