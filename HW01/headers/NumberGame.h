#ifndef __PUZZLE__
#define __PUZZLE__
#include <stdio.h>
#include <stdlib.h>
#include "../headers/main.h"
#include "../headers/PictureManipulation.h"
#include <time.h>
#define SHUFFLE_COUNT 100
#define ROWS 3
#define COLS 3
#define ZERO 0
#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4

void randomMatrix(int* mat,  int rows,  int cols);
void Game(int* mat,  int rows,  int cols);
int findZero( int* puzzle,  int rows,  int cols);
void swapPieces(int* f_index, int* s_index);
int checkWin(int* mat, int rows, int cols);
int indexValue(int* mat, int size, int num);
void initializeMatrix(int* mat, int rows, int cols);
void printMatrix(int* mat, int rows, int cols);
int checkUp(int* mat, int rows, int cols, int new_piece_index);
int checkRight(int* mat, int rows, int cols, int new_piece_index);
int checkDown(int* mat, int rows, int cols, int new_piece_index);
int checkLeft(int* mat, int rows, int cols, int new_piece_index);

#endif
