/*
* @author: Dawid Kopiczko
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// Global variables.
int PLAYER_ID;
int NUM_OF_PLAYERS;
int PENG_PER_PLAYER;
int WIDTH;
int HEIGHT;


// Global functions.
void LoadData(char* input);
void WriteData(char* output);
int GetField(int x, int y);
void SetField(int x, int y, int value);
int GetScore(int id);
void SetScore(int id, int value);
int* GetPenguin(int index);
void SetPenguin(int index, int x, int y);
void ShowData();
void MakePlacement(int* input);
void MakeMovement(int* input);
int CheckPosition(int* position);
void ChangePosition(int* position, int direction);
int GetUserInput(int isPlacementPhase, int* input);
int ChooseInput(int isPlacementPhase, int* input);


// Local functions.
void  getInput(int isInteractiveMode, int isPlacementPhase, int* input);


////	MAIN	////

int main(int argc, char** argv) {
	// [x, y] for placement and [penguin_index, direction, distance] for movement
	int input[3]; 
	int isPlacementPhase, isInteractiveMode;
	
	if (argc < 6) {
		printf("Arguments missing");
		exit(1);
	}

	isPlacementPhase = atoi(argv[1]);
	isInteractiveMode = atoi(argv[2]);
	PLAYER_ID = atoi(argv[3]);

	LoadData(argv[4]);

	if (isInteractiveMode)
		ShowData();

	getInput(isInteractiveMode, isPlacementPhase, input);

	if (isPlacementPhase)
		MakePlacement(input);
	else
		MakeMovement(input);

	ShowData();

	WriteData(argv[5]);

	return 0;
}


////	LOCAL	////

void getInput(int isInteractiveMode, int isPlacementPhase, int* input) {
	int valid;

	while (1) {
		// GetInput gets user's input, while ChooseInput determines and returns input.
		// If user types invalid data, GetUserInput returns 0.
		valid = (isInteractiveMode) ? GetUserInput(isPlacementPhase, input) : ChooseInput(isPlacementPhase, input);

		if (valid)
			break;
		else
			printf("Invalid input.\n");
	}
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
		if (j % 2)
			printf("    ");

		for (i = 0; i < WIDTH; i++) {
			if (GetField(i, j) < 0) {
				if(GetField(i, j) == -PLAYER_ID)
					for (k = 0; k < PENG_PER_PLAYER; k++) {
						if (GetPenguin(k)[0] == i && GetPenguin(k)[1] == j)
							printf("( %d )  ", k);
					}
				else
					printf(" %d    ", GetField(i, j));
			}
			else
				printf("  %d    ", GetField(i, j));
		}
		printf("\n\n\n");
	}
	printf("\n");

	printf("Scores: \n\n");
	for (i = 1; i <= NUM_OF_PLAYERS; i++) {
		printf("Player %d: %d ", i, GetScore(i));
		printf("\n");
	}
}
void MakePlacement(int* input) {
	int i, x, y;
	x = input[0];
	y = input[1];

	for(i = 0; i < PENG_PER_PLAYER; i++){
		printf("%d\n", GetPenguin(i)[0]);
		if(GetPenguin(i)[0] == -1){
			SetPenguin(i, x, y);
			SetField(x, y, -PLAYER_ID);
			SetScore(PLAYER_ID, 1);
			break;
		}
	}
}
int GetUserInput(int isPlacementPhase, int* input) {
	int i1, i2, i3;

	if(isPlacementPhase){
		printf("\nChoose: x and y coordinates.\n\n");
		scanf("%d %d", &i1, &i2);

		input[0] = i1;
		input[1] = i2;

		if(GetField(i1, i2) == 1)
			return 1;
		else
			return 0;
	}
	else{
		printf("\nChoose: peng index, direction and distance.\n\n");
		scanf("%d %d %d", &i1, &i2, &i3);

		input[0] = i1;
		input[1] = i2;
		input[2] = i3;

		return 1;
	}

	return 0;
}
int ChooseInput(int isPlacementPhase, int* input) {
	int seed, i, j;
	int pos[2];
	time_t tt;
	
	seed = time(&tt);
	srand(seed);

	if(isPlacementPhase){
		// Not implemented.
	}
	else{
		input[0] = rand() % PENG_PER_PLAYER;
		for(j = 0; j < PENG_PER_PLAYER; j++)
			for(i = 0; i < 50; i++){
				pos[0] = GetPenguin(input[0])[0];
				pos[1] = GetPenguin(input[0])[1];
				input[1] = rand() % 6;
				input[2] = rand() % 5;
				ChangePosition(pos, input[1]);
				if(CheckPosition(pos))
					return 1;
			}
		return 1;
	}

	return 0;
}