/*
* @author: Dawid Kopiczko
*/

#include <stdio.h>


// Global functions.
void LoadData();
void WriteData();
int GetField(int x, int y);
void SetField(int x, int y, int value);
int GetScore(int id);
void SetScore(int id, int value);
void ShowData();
void MakePlacement(int* input);
void MakeMovement(int* input);
int* GetUserInput(isPlacementPhase);
int* ChooseInput(isPlacementPhase);


// Global variables.
int PLAYER_ID;
int NUM_OF_PLAYERS;
int PENG_PER_PLAYER;
int WIDTH;
int HEIGHT;
int* BOARD;
int* SCORES;


// Local functions.
int* getInput(int isInteractiveMode, int isPlacementPhase);


////	MAIN	////

int main(int argc, char** argv) {
	// [x, y] for placement and [direction, distance] for movement
	int* input; 
	int isPlacementPhase, isInteractiveMode;
	
	isPlacementPhase = atoi(argv[1]);
	isInteractiveMode = atoi(argv[2]);
	PLAYER_ID = atoi(argv[3]);

	LoadData();

	input = getInput(isInteractiveMode, isPlacementPhase);

	if (isPlacementPhase)
		MakePlacement(input);
	else
		MakeMovement(input);

	if (isInteractiveMode)
		ShowData();

	WriteData();

	return 0;
}


////	LOCAL	////

int* getInput(int isInteractiveMode, int isPlacementPhase) {
	int* input;

	while (1) {
		// GetInput gets user's input, while ChooseInput determines and returns input.
		// If user types invalid data, GetUserInput returns 0.
		input = (isInteractiveMode) ? GetUserInput(isPlacementPhase) : ChooseInput(isPlacementPhase);

		if (!input)
			break;
		else
			printf("Invalid input.\n");
	}

	return input;
}




// Temporary functions.
void ShowData() {
	printf("%d\n", WIDTH);
	printf("%d\n", HEIGHT);
	printf("%d\n", NUM_OF_PLAYERS);
	printf("%d\n", PENG_PER_PLAYER);
	printf("\n");


	int i, j;

	for (j = 0; j < HEIGHT; j++) {
		for (i = 0; i < WIDTH; i++) {
			printf("%d ", GetField(i, j));
		}
		printf("\n");
	}
	printf("\n");

	for (i = 1; i <= NUM_OF_PLAYERS; i++) {
		printf("%d ", GetScore(i));
		printf("\n");
	}
}
void MakePlacement(int* input) {}
void MakeMovement(int* input) {}
int* GetUserInput(isPlacementPhase) { return 0; }
int* ChooseInput(isPlacementPhase) { return 0; }