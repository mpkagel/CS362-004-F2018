#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

void assertEquality(int a, int b, char* message, int* result, int* test_failures, int test_failure_index) {
	if (a != b) {
		printf(message);
		*result = 0;
		if (test_failures != NULL) {
			test_failures[test_failure_index] = 0;
		}
	}
}

void printRandomState(struct gameState g) {
	int i, j, k;
	int newline_offset = 8;		
	printf("numPlayers: %d\n", g.numPlayers);
	printf("supplyCounts:\n");
	j = 0;
	for (i = 0; i < treasure_map + 1; i++) {
		printf("%d: %d;  ", i, g.supplyCount[i]);
		if (j > newline_offset) {
			j = 0;
			printf("\n");
		} else {
			j++;
		}
	}
	printf("\nembargoTokens:\n");
	j = 0;
	for (i = 0; i < treasure_map + 1; i++) {
		printf("%d: %d;  ", i, g.embargoTokens[i]);
		if (j > newline_offset) {
			j = 0;
			printf("\n");
		} else {
			j++;
		}
	}
	printf("\noutpostPlayed: %d;  outpostTurn: %d;  whoseTurn: %d;  phase: %d;\n",
					g.outpostPlayed, g.outpostTurn, g.whoseTurn, g.phase);
	printf("numActions: %d;  coins: %d;  numBuys: %d;\n",
					g.numActions, g.coins, g.numBuys);
	printf("hand:\n");
	k = 0;
	for (i = 0; i < g.numPlayers; i++) {
		printf("player %d:\n", i);
		for (j = 0; j < g.handCount[i]; j++) {
			printf("%d: %d;  ", j, g.hand[i][j]);		
  		if (k > newline_offset) {
  			k = 0;
  			printf("\n");
  		} else {
  			k++;
  		}
		}
		k = 0;
		printf("\n");
	}
	printf("handCount:\n");
	j = 0;
	for (i = 0; i < g.numPlayers; i++) {   		
  	printf("%d: %d;  ", i, g.handCount[i]);
  	if (j > newline_offset) {
  		j = 0;
  		printf("\n");
  	} else {
  		j++;
  	}
  }
	printf("\n");
	printf("deck:\n");
	k = 0;
	for (i = 0; i < g.numPlayers; i++) {
		printf("player %d:\n", i);
		for (j = 0; j < g.deckCount[i]; j++) {
			printf("%d: %d;  ", j, g.deck[i][j]);		
  		if (k > newline_offset) {
  			k = 0;
  			printf("\n");
  		} else {
  			k++;
  		}
		}
		k = 0;
		printf("\n");
	}
	printf("deckCount:\n");
	j = 0;
	for (i = 0; i < g.numPlayers; i++) {   		
  	printf("%d: %d;  ", i, g.deckCount[i]);
  	if (j > newline_offset) {
  		j = 0;
  		printf("\n");
  	} else {
  		j++;
  	}
  }
	printf("\n");
	printf("discard:\n");
	k = 0;
	for (i = 0; i < g.numPlayers; i++) {
		printf("player %d:\n", i);
		for (j = 0; j < g.discardCount[i]; j++) {
			printf("%d: %d;  ", j, g.discard[i][j]);		
  		if (k > newline_offset) {
  			k = 0;
  			printf("\n");
  		} else {
  			k++;
  		}
		}
		k = 0;
		printf("\n");
	}
	printf("discardCount:\n");
	j = 0;
	for (i = 0; i < g.numPlayers; i++) {   		
  	printf("%d: %d;  ", i, g.discardCount[i]);
  	if (j > newline_offset) {
  		j = 0;
  		printf("\n");
  	} else {
  		j++;
  	}
  }
	printf("\n");
	printf("playedCards:\n");
	j = 0;
	for (i = 0; i < g.playedCardCount; i++) {   		
  	printf("%d: %d;  ", i, g.playedCards[i]);
  	if (j > newline_offset) {
  		j = 0;
  		printf("\n");
  	} else {
  		j++;
  	}
  }
	printf("\n");
	printf("playedCardCount: %d\n", g.playedCardCount);
}

int compareGameStateTest1(int numPlayers, struct gameState g, struct gameState testg, int p, int handPos, int testNum, int* test_failures) {
	int i, j;
	int result = 1;	
	char message[512];
	char functionName[256];
  sprintf(functionName, "compareGameStateTest1 test#: %d", testNum);

	// *************** Compare gameStates ***************
	// numPlayers
	if (test_failures[0] == 1) {
		sprintf(message, "FAILED: %s numPlayers\n", functionName);
		assertEquality(g.numPlayers, testg.numPlayers, message, &result, test_failures, 0);
	}
	// supplyCount
	if (test_failures[1] == 1) {
		for (i = 0; i < treasure_map + 1; i++) {
			sprintf(message, "FAILED: %s supplyCount card %d\n", functionName, i);
			assertEquality(g.supplyCount[i], testg.supplyCount[i], message, &result, test_failures, 1);
		}
	}
	// embargoTokens
	if (test_failures[2] == 1) {
		for (i = 0; i < treasure_map + 1; i++) {
			sprintf(message, "FAILED: %s embargoTokens card %d\n", functionName, i);
			assertEquality(g.embargoTokens[i], testg.embargoTokens[i], message, &result, test_failures, 2);
		}
	}
	// outpostPlayed
	if (test_failures[3] == 1) {
		sprintf(message, "FAILED: %s outpostPlayed\n", functionName);
		assertEquality(g.outpostPlayed, testg.outpostPlayed, message, &result, test_failures, 3);
	}
	// outpostTurn
	if (test_failures[4] == 1) {
		sprintf(message, "FAILED: %s outpostTurn\n", functionName);
		assertEquality(g.outpostTurn, testg.outpostTurn, message, &result, test_failures, 4);
	}
	// whoseTurn
	if (test_failures[5] == 1) {
		sprintf(message, "FAILED: %s whoseTurn\n", functionName);
		assertEquality(g.whoseTurn, testg.whoseTurn, message, &result, test_failures, 5);
	}
	// phase
	if (test_failures[6] == 1) {
		sprintf(message, "FAILED: %s phase\n", functionName);
		assertEquality(g.phase, testg.phase, message, &result, test_failures, 6);
	}
	// numActions
	if (test_failures[7] == 1) {
		sprintf(message, "FAILED: %s numActions\n", functionName);
		assertEquality(g.numActions, testg.numActions, message, &result, test_failures, 7);
	}
	// coins
	if (test_failures[8] == 1) {
		sprintf(message, "FAILED: %s coins\n", functionName);	
		assertEquality(g.coins, testg.coins, message, &result, test_failures, 8);
	}
	// numBuys
	if (test_failures[9] == 1) {
		sprintf(message, "FAILED: %s numBuys\n", functionName);	
		assertEquality(g.numBuys, testg.numBuys, message, &result, test_failures, 9);
	}
	// hand
	if (test_failures[10] == 1) {
		for (i = 0; i < numPlayers; i++) {
			for (j = 0; j < g.handCount[i]; j++) {	
				sprintf(message, "FAILED: %s hand player %d, pos %d\n", functionName, i, j);			
				assertEquality(g.hand[i][j], testg.hand[i][j], message, &result, test_failures, 10);
			}
		}	
	}
	// handCount
	if (test_failures[11] == 1) {
		for (i = 0; i < numPlayers; i++) {
			sprintf(message, "FAILED: %s handCount player %d\n", functionName, i);			
			assertEquality(g.handCount[i], testg.handCount[i], message, &result, test_failures, 11); 
		}			
	}
	// deck
	if (test_failures[12] == 1) {
		for (i = 0; i < numPlayers; i++) {
			for (j = 0; j < g.deckCount[i]; j++) {
				sprintf(message, "FAILED: %s deck player %d, pos %d\n", functionName, i, j);			
				assertEquality(g.deck[i][j], testg.deck[i][j], message, &result, test_failures, 12);
			}
		}
	}
	// deckCount
	if (test_failures[13] == 1) {
		for (i = 0; i < numPlayers; i++) {
			sprintf(message, "FAILED: %s deckCount player %d\n", functionName, i);			
			assertEquality(g.deckCount[i], testg.deckCount[i], message, &result, test_failures, 13);
		}
	}
	// discard
	if (test_failures[14] == 1) {
		for (i = 0; i < numPlayers; i++) {
			for (j = 0; j < g.discardCount[i]; j++) {
				sprintf(message, "FAILED: %s discard player %d, pos %d\n", functionName, i, j);					
				assertEquality(g.discard[i][j], testg.discard[i][j], message, &result, test_failures, 14);
			}
		}
	}
	// discardCount
	if (test_failures[15] == 1) {
		for (i = 0; i < numPlayers; i++) {
			sprintf(message, "FAILED: %s discardCount player %d\n", functionName, i);			
			assertEquality(g.discardCount[i], testg.discardCount[i], message, &result, test_failures, 15);
		}
	}
	// playedCards
	if (test_failures[16] == 1) {
		for (i = 0; i < g.playedCardCount; i++) {
			sprintf(message, "FAILED: %s playedCards %d\n", functionName, i);			
 			assertEquality(g.playedCards[i], testg.playedCards[i], message, &result, test_failures, 16);
		}
	}
	// playedCardCount
	if (test_failures[17] == 1) {
		sprintf(message, "FAILED: %s playedCardCount\n", functionName);	
		assertEquality(g.playedCardCount, testg.playedCardCount, message, &result, test_failures, 17);
	}

	return result;

}

int main() {
	//int k[10] = { adventurer, gardens, embargo, village, minion,
	//				mine, cutpurse, sea_hag, tribute, smithy };
	struct gameState g, testg;
	int numPlayers = 2;
	char message[512];
	int numTests = 5000;
	int i, j, k, n, p, handPos, outcome, result;		
	int all_test_result = 1;
	int test_failures[18] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}; 
	int testg_treasure;
	int next_card;                              	
	int testg_temp_hand[1024];
	int testg_temp_hand_size;
	int deckPos, discardPos;

	printf("-----  Random Testing Adventurer card  -----\n");

	for (n = 0; n < numTests; n++) {
		for (i = 0; i < sizeof(struct gameState); i++) {
			((char*)&g)[i] = floor(Random() * 256);
		}
		g.numPlayers = numPlayers;
		for (j = 0; j < treasure_map + 1; j++) {
			g.supplyCount[j] = floor(Random() * 11);
		}
		for (j = 0; j < treasure_map + 1; j++) {
			g.embargoTokens[j] = 0;
		}
		for (j = 0; j < g.numPlayers; j++) {
			g.deckCount[j] = floor(Random() * 80) + 1;
			g.discardCount[j] = floor(Random() * 300) + 1;
			g.handCount[j] = floor(Random() * 30) + 1;	
		}
		for (j = 0; j < g.numPlayers; j++) {
			for (k = 0; k < g.deckCount[j]; k++) {
				g.deck[j][k] = floor(Random() * (treasure_map + 1));
			}
		}	
		for (j = 0; j < g.numPlayers; j++) {
 			for (k = 0; k < g.discardCount[j]; k++) {
 				g.discard[j][k] = floor(Random() * (treasure_map + 1));
 			}
 		}	
		for (j = 0; j < g.numPlayers; j++) {
			for (k = 0; k < g.handCount[j]; k++) {
				g.hand[j][k] = floor(Random() * (treasure_map + 1));
			}
		}
		g.playedCardCount = floor(Random() * 200);
		for (j = 0; j < g.playedCardCount; j++) {	
  		g.playedCards[j] = floor(Random() * (treasure_map + 1));
  	}
		p = floor(Random() * g.numPlayers);
		g.coins = floor(Random() * 100);
		g.whoseTurn = p;		
		handPos = floor(Random() * g.handCount[p]);
		deckPos = floor(Random() * g.deckCount[p]);
		discardPos = floor(Random() * g.discardCount[p]);
		g.hand[p][handPos] = adventurer;
		g.deck[p][deckPos] = copper;
		g.discard[p][discardPos] = silver;
		memcpy(&testg, &g, sizeof(struct gameState));	

		outcome = cardEffect(adventurer, 0, 0, 0, &g, handPos, 0);
	
		// Artificially make the test game state have the treasure cards drawn from
		// playing the adventurer card in the game state g
		testg_treasure = 0;
		testg_temp_hand_size = 0;
		while (testg_treasure < 2) {
			if (testg.deckCount[p] < 1) {
				memcpy(testg.deck[p], g.deck[p], sizeof(int) * testg.discardCount[p]);
				testg.deckCount[p] = testg.discardCount[p];
				testg.discardCount[p] = 0;
			} else {
				next_card = testg.deck[p][testg.deckCount[p] - 1];
				if (next_card == copper || next_card == silver || next_card == gold) {
					if (testg_treasure == 0) {
						testg.playedCardCount++;
						testg.playedCards[testg.playedCardCount - 1] = testg.hand[p][handPos];
						testg.hand[p][handPos] = next_card;
					} else {
						testg.handCount[p]++;		
						testg.hand[p][testg.handCount[p] - 1] = next_card;
					}					
					testg_treasure++;
				} else {
					testg_temp_hand_size++;
					testg_temp_hand[testg_temp_hand_size - 1] = next_card;		
				}
				testg.deckCount[p]--;	
			}
		}
		for (j = testg_temp_hand_size - 1; j >= 0; j--) {                   	
  		testg.discardCount[p]++;                                			
  		testg.discard[p][testg.discardCount[p] - 1] = testg_temp_hand[j];	
  	}

		result = compareGameStateTest1(numPlayers, g, testg, p, handPos, n, test_failures);
		if (!result) {
			printf("****** Test %d Player %d plays Adventurer from handPos %d ******\n", n, p, handPos);
			printf("TEST failed\n");
			all_test_result = 0;
			printf("------- gameState g... -------\n");
			printRandomState(g);
			printf("------- gameState testg... -------\n");
			printRandomState(testg);
			printf("*************************** Test %d Done *****************************\n\n", n);
		} else {
			sprintf(message, "FAIL: Test %d Adventurer card outcome should be 0\n", n);
			assertEquality(outcome, 0, message, &result, NULL, 0);
			if (outcome) {
				printf("****** Test %d Player %d plays Adventurer from handPos %d ******\n", n, p, handPos);			
				printf("TEST failed\n");
				all_test_result = 0;
				printf("------- gameState g... -------\n");
				printRandomState(g);
				printf("------- gameState testg... -------\n");
				printRandomState(testg);
				printf("*************************** Test %d Done *****************************\n\n", n);
			}
		}
	}

	if (all_test_result) {
		printf("\n+++++ : PASS, randomtestadventurer passed.\n");
	} else {
		printf("\n+++++ : FAIL, randomtestadventurer failed.\n");	
	}

	return 0;
}

