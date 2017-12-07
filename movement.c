/*
* @author: Dawid Kopiczko
*
* File provides function:
* -  void MakeMovement(int* input)
*	It move target penguin in target direction for target distance from input.
*	Also checks for possibility of this action and updates data.
* -  void ChangePosition(int* position, int direction)
*	It returns changed array with coordinates. It makes change by 'moving' in target direction.
* -  int CheckPosition(int* position)
*	It checks if target position is possible to move into.
*/

#include <stdio.h>


// Global variables.
int PLAYER_ID;
int WIDTH;
int HEIGHT;


// Global functions.
int* GetPenguin(int index);
void SetPenguin(int index, int x, int y);
int GetField(int x, int y);
void SetField(int x, int y, int value);
int GetScore(int id);
void SetScore(int id, int value);
void ChangePosition(int* position, int direction);


// Local functions.
static void updateData(int penguin_index, int* last_position);


////	GLOBAL	////

void MakeMovement(int* input) {
	int i, penguin, direction, distance;
	int position[2];
	int last_position[2];

	penguin = input[0];
	direction = input[1];
	distance = input[2];

	// Helper variables with position.
	last_position[0] = GetPenguin(penguin)[0];
	last_position[1] = GetPenguin(penguin)[1];
	position[0] = last_position[0];
	position[1] = last_position[1];

	for (i = 0; i < distance; i++) {
		// Changes position by one step.
		ChangePosition(position, direction);
		// Checks if movement is possible.
		if (CheckPosition(position))
			SetPenguin(penguin, position[0], position[1]);
		else
			break;
	}

	if(GetPenguin(penguin)[0] != last_position[0] || GetPenguin(penguin)[1] != last_position[1])
		updateData(penguin, last_position);
}

void ChangePosition(int* position, int direction) {
	int* x;
	int* y;

	x = position;
	y = position + 1;

	switch (direction) {
		// Up-Right
		case 0:
			*x += (*y % 2) ? 1 : 0;
			*y += -1;
			break;

		// Right
		case 1:
			*x += 1;
			break;

		// Down-Right
		case 2:
			*x += (*y % 2) ? 1 : 0;
			*y += 1;
			break;

		// Down-Left
		case 3:
			*x += (*y % 2) ? 0 : -1;
			*y += 1;
			break;

		// Left
		case 4:
			*x += -1;
			break;

		// Up-Left
		case 5:
			*x += (*y % 2) ? 0 : -1;
			*y += -1;
			break;

		default:
			break;
	}
}

int CheckPosition(int* position) {
	int x, y, value;

	x = position[0];
	y = position[1];
	value = GetField(x, y);

	if (value > 0 && x >= 0 && x < WIDTH && y >= 0 & y < HEIGHT)
		return 1;
	else
		return 0;
}


////	LOCAL	////
static void updateData(int penguin_index, int* last_position) {
	int fish, score;
	int* position;

	position = GetPenguin(penguin_index);
	fish = GetField(position[0], position[1]);
	score = GetScore(PLAYER_ID);

	printf("%d\n", GetField(last_position[0], last_position[1]));
	SetField(last_position[0], last_position[1], 0);
	SetField(position[0], position[1], -PLAYER_ID);
	printf("%d\n", GetField(last_position[0], last_position[1]));

	SetScore(PLAYER_ID, score + fish);
}