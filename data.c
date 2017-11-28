/*
* @author: Dawid Kopiczko
*
* File provides functions:
* -  void LoadData()
*	Loads data from input file and assigns it to global variables.
* -  void WriteData()
*	Writes data from variables to output file.
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
*/

#include <stdio.h>


// Global variables.
int NUM_OF_PLAYERS;
int PENG_PER_PLAYER;
int WIDTH;
int HEIGHT;
int* BOARD;
int* SCORES;

// Local variables.
static FILE* input_file;
static FILE* output_file;

// Local functions.
static void openFiles(char* input, char* output);
static void closeFiles();
static void allocateMemory();
static void loadSettings();
static void loadBoard();
static void loadScores();
static void writeSettings();
static void writeBoard();
static void writeScores();


////	GLOBAL	////

void LoadData() {
	openFiles("input.txt", "output.txt");
	loadSettings();
	allocateMemory();
	loadBoard();
	loadScores();
}

void WriteData() {
	writeSettings();
	writeBoard();
	writeScores();
	closeFiles();
}

int GetField(int x, int y) {
	return *(BOARD + y * WIDTH + x);
}

void SetField(int x, int y, int value) {
	*(BOARD + y * WIDTH + x) = value;
}

int GetScore(int id) {
	return *(SCORES + id - 1);
}

void SetScore(int id, int value) {
	*(SCORES + id - 1) = value;
}


////	LOCAL	////

static void openFiles(char* input, char* output) {
	input_file = fopen(input, "r");
	output_file = fopen(output, "w");
}

static void closeFiles() {
	fclose(input_file);
	fclose(output_file);
}

static void allocateMemory() {
	BOARD = (int*)calloc(WIDTH * HEIGHT, sizeof(int));
	SCORES = (int*)calloc(NUM_OF_PLAYERS, sizeof(int));
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