#ifndef __PICTURE__
#define __PICTURE__
#include <stdio.h>
#include <stdlib.h>
#include "../headers/main.h"
#include "../headers/PictureManipulation.h"
#include "../headers/NumberGame.h"


#define ROWS 3
#define COLS 3

void matrixRandom(int* mat, int rows, int cols, int from_num, int to_num);
void vertically(int* mat, int rows, int cols);
void horizontally(int* mat, int rows, int cols);
void nintyDegreeForward(int* mat,  int rows,  int cols);
void nintyDegreeBack(int* mat, int rows, int cols);
void nintyDegreeForwardRotate(int* start_index, int* end_index,  int rows,  int cols,  int cell_jump);
void nintyDegreeBackRotate(int* start_index, int* end_index,  int rows,  int cols,  int cell_jump);
void HorizontalFlip(int* start_index, int* end_index,  int rows,  int cols);
void verticallyFlip(int* start_index, int* end_index,  int rows, int cols);



#endif
