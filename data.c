/*
* @author: Dawid Kopiczko
*
* File provides functions:
* -  void LoadData(char* input)
*	Loads data from input file and assigns it to global variables.
*	Where input is a name of text file.
* -  void WriteData(char* output)
*	Writes data from variables to output file.
*	Where output is a name of text file.
* -  int GetField(int x, int y)
*	Where x and y are coordinates of board.
*	Returns int with the value of target field.
* -  void SetField(int x, int y, int value)
*	Where x and y are coordinates of board.
*	Sets value to the field.
* -  int GetScore(int id)
*	Where id is number of player.
*	Returns int with the score of target player.
* -  void SetScore(int id, int value)
*	Where id is number of player.
*	Sets value as a score of target player.
* -  int* GetPenguin(int index)
*	Where index is the index of penguin.
*	Returns position [x, y] of target penguin.
* -  void SetPenguin(int index, int x, int y)
*	Where index is the index of penguin.
*	Sets position [x, y] of target penguin.
*/

#include <stdio.h>


// Global variables.
int PLAYER_ID;
int NUM_OF_PLAYERS;
int PENG_PER_PLAYER;
int WIDTH;
int HEIGHT;

// Local variables.
static FILE* input_file;
static FILE* output_file;
static int* board;
static int* scores;
static int* penguins;

// Local functions.
static void openFile(char* filename, int type);
static void closeFile(int type);
static void allocateMemory();
static void loadSettings();
static void loadBoard();
static void loadScores();
static void writeSettings();
static void writeBoard();
static void writeScores();
static void findPenguins();


////	GLOBAL	////

void LoadData(char* input) {
	openFile(input, 0);
	loadSettings();
	allocateMemory();
	loadBoard();
	loadScores();
	findPenguins();
	closeFile(0);
}

void WriteData(char* output) {
	openFile(output, 1);
	writeSettings();
	writeBoard();
	writeScores();
	closeFile(1);
}

int GetField(int x, int y) {
	return *(board + y * WIDTH + x);
}

void SetField(int x, int y, int value) {
	*(board + y * WIDTH + x) = value;
}

int GetScore(int id) {
	return *(scores + id - 1);
}

void SetScore(int id, int value) {
	*(scores + id - 1) = value;
}

int* GetPenguin(int index) {
	return (penguins + index * 2);
}

void SetPenguin(int index, int x, int y) {
	*(penguins + index * 2) = x;
	*(penguins + index * 2 + 1) = y;
}


////	LOCAL	////

static void openFile(char* filename, int type) {
	// 0 - input  1 - output
	if(type)
		output_file = fopen(filename, "w");
	else
		input_file = fopen(filename, "r");
}

static void closeFile(int type) {
	// 0 - input  1 - output
	if(type)
		fclose(output_file);
	else
		fclose(input_file);
}

static void allocateMemory() {
	board = (int*)calloc(WIDTH * HEIGHT, sizeof(int));
	scores = (int*)calloc(NUM_OF_PLAYERS, sizeof(int));
	penguins = (int*)calloc(PENG_PER_PLAYER * 2, sizeof(int));
}

static void loadSettings() {
	fscanf(input_file, "%d", &WIDTH);
	fscanf(input_file, "%d", &HEIGHT);
	fscanf(input_file, "%d", &NUM_OF_PLAYERS);
	fscanf(input_file, "%d", &PENG_PER_PLAYER);
}

static void loadBoard() {
	int i, j, value;

	for (j = 0; j < HEIGHT; j++)
		for (i = 0; i < WIDTH; i++) {
			fscanf(input_file, "%d", &value);
			SetField(i, j, value);
		}
}

static void loadScores() {
	int i, value;

	for (i = 1; i <= NUM_OF_PLAYERS; i++) {
		fscanf(input_file, "%d", &value);
		SetScore(i, value);
	}
}

static void writeSettings() {
	fprintf(output_file, "%d\n", WIDTH);
	fprintf(output_file, "%d\n", HEIGHT);
	fprintf(output_file, "%d\n", NUM_OF_PLAYERS);
	fprintf(output_file, "%d\n", PENG_PER_PLAYER);
}

static void writeBoard() {
	int i, j;

	for (j = 0; j < HEIGHT; j++) {
		for (i = 0; i < WIDTH; i++)
			fprintf(output_file, "%d ", GetField(i, j));

		fprintf(output_file, "\n");
	}
}

static void writeScores() {
	int i;

	for (i = 1; i <= NUM_OF_PLAYERS; i++)
		fprintf(output_file, "%d\n", GetScore(i));
}

static void findPenguins() {
	int i, j, index;

	index = 0;

	for (j = 0; j < HEIGHT; j++)
		for (i = 0; i < WIDTH; i++)
			if (GetField(i, j) == -PLAYER_ID)
				SetPenguin(index++, i, j);

	for(; index < PENG_PER_PLAYER; index++)
		SetPenguin(index, -1, -1);
}