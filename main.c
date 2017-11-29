/*
* @author: Dawid Kopiczko
*/

#include <stdio.h>


// Global variables.
int PLAYER_ID;
int NUM_OF_PLAYERS;
int PENG_PER_PLAYER;
int WIDTH;
int HEIGHT;


// Global functions.
void LoadData();
void WriteData();
int GetField(int x, int y);
void SetField(int x, int y, int value);
int GetScore(int id);
void SetScore(int id, int value);
int* GetPenguin(int index);
void SetPenguin(int index, int x, int y);
void ShowData();
void MakePlacement(int* input);
void MakeMovement(int* input);
int* GetUserInput(int isPlacementPhase);
int* ChooseInput(int isPlacementPhase);


// Local functions.
int* getInput(int isInteractiveMode, int isPlacementPhase);


////	MAIN	////

int main(int argc, char** argv) {
	// [x, y] for placement and [penguin_index, direction, distance] for movement
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
	int i, j, k;

	printf("\n");
	printf("WIDTH: %d\n", WIDTH);
	printf("HEIGHT: %d\n", HEIGHT);
	printf("NUM_OF_PLAYERS: %d\n", NUM_OF_PLAYERS);
	printf("PENG_PER_PLAYER: %d\n", PENG_PER_PLAYER);
	printf("PENGS: ");
	for(i = 0; i < PENG_PER_PLAYER; i++)
		printf("(%d, %d) ", GetPenguin(i)[0], GetPenguin(i)[1]);
	printf("\n");
	printf("\n");


	for (j = 0; j < HEIGHT; j++) {
		for (i = 0; i < WIDTH; i++) {
			if (GetField(i, j) < 0) {
				if(GetField(i, j) == -PLAYER_ID)
					for (k = 0; k < PENG_PER_PLAYER; k++) {
						if (GetPenguin(k)[0] == i && GetPenguin(k)[1] == j)
							printf("( %d )", k);
					}
				else
					printf(" %d  ", GetField(i, j));
			}
			else
				printf("  %d  ", GetField(i, j));
		}
		printf("\n");
	}
	printf("\n");

	printf("Scores: \n\n");
	for (i = 1; i <= NUM_OF_PLAYERS; i++) {
		printf("Player %d: %d ", i, GetScore(i));
		printf("\n");
	}
}
void MakePlacement(int* input) {}
void MakeMovement(int* input) {}
int* GetUserInput(int isPlacementPhase) { return 0; }
int* ChooseInput(int isPlacementPhase) { return 0; }