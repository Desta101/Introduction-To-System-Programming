#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../headers/NumberGame.h"
#include "../headers/PictureManipulation.h"

void NumberGame()
{
	int mat[ROWS][COLS];
	Game((int*)mat, ROWS, COLS);
}


void randomMatrix(int* mat,  int rows,  int cols)
{
    int start , newStart;
    start = findZero(( int*)mat, rows, cols);
    for (int i = 0; i < SHUFFLE_COUNT; i++)
    {
        switch (rand() % 4 + 1)
        {
        case UP:
            newStart = start - cols;
            if (checkUp(( int*)mat, rows, cols, newStart))
            {
                swapPieces(mat + start, mat + newStart);
                start = newStart;
            }
            break;
        case RIGHT:
            newStart = start + 1;
            if (checkRight(( int*)mat, rows, cols, newStart))
            {
                swapPieces(mat + start, mat + newStart);
                start = newStart;
            }
            break;
        case DOWN:
            newStart = start + cols;
            if (checkDown(( int*)mat, rows, cols, newStart))
            {
                swapPieces(mat + start, mat + newStart);
                start = newStart;
            }
            break;
        case LEFT:
            newStart = start - 1;
            if (checkLeft(( int*)mat, rows, cols, newStart))
            {
                swapPieces(mat + start, mat + newStart);
                start = newStart;
            }
            break;
        default:
            break;
        }
    }
}

void Game(int* mat,  int rows,  int cols)
{
    int step ,start;
    initializeMatrix(mat, rows, cols);

    do
    {
        randomMatrix(mat, rows, cols);
    } while(checkWin(( int*)mat, rows, cols));

    start = findZero(( int*)mat, rows, cols);
    while(1)
    {
		printMatrix((int*)mat, rows, cols);
        printf("\n");
        printf("Your step: ");
        scanf("%d", &step);
        if (step < 0 || step > rows * cols - 1)
        {
            printf("Invalid step\n\n");
            continue;
        }
        else
        {
            int index = indexValue(( int*)mat, (rows * cols), step);
            if (index == start - cols)
            {
                if (checkUp(mat, rows, cols, index))
                {
                    swapPieces(mat + start, mat + index);
                    start = index;
                }
                else
                {
                    printf("Invalid step\n\n");
                    continue;
                }
            }
            else if (index == start + 1)
            {
                if (checkRight(mat, rows, cols, index))
                {
                    swapPieces(mat + start, mat + index);
                    start = index;
                }
                else
                {
                    printf("Invalid step\n\n");
                    continue;
                }
            }
            else if (index == start + cols)
            {
                if (checkDown(mat, rows, cols, index))
                {
                    swapPieces(mat + start, mat + index);
                    start = index;
                }
                else
                {
                    printf("Invalid step\n\n");
                    continue;
                }
            }
            else if (index == start - 1)
            {
                if (checkLeft(mat, rows, cols, index))
                {
                    swapPieces(mat + start, mat + index);
                    start = index;
                }
                else
                {
                    printf("Invalid step\n\n");
                    continue;
                }
            }
            else
            {
                printf("Invalid step\n\n");
                continue;
            }
            if (checkWin(( int*)mat, rows, cols))
            {
                printf("You win! The game is over!\n");
                exit(0);
            }
        }  
    }
}

int findZero( int* mat,  int rows,  int cols)
{
    for (int i = 0; i < rows * cols - 1; i++)
    {
        if (*(mat + i) == 0)
        {
            return i;
        }
    }
    return -1;
}

void swapPieces(int* f_index, int* s_index)
{
    int temp = *f_index;
    *f_index = *s_index;
    *s_index = temp;
}

int checkUp( int* mat,  int rows,  int cols,  int new_piece_index)
{
    int flag = new_piece_index;
    if (flag >= 0)
    {
        return 1;
    }
    return 0;
}

int checkRight( int* mat,  int rows,  int cols,  int new_piece_index)
{
    int flag = (new_piece_index) % cols;
    if ((new_piece_index != (cols * rows)) && flag)
    {
        return 1;
    }
    return 0;
}

int checkDown( int* mat,  int rows,  int cols,  int new_piece_index)
{
    int flag = new_piece_index;
    if (flag <= (rows * cols) - 1)
    {
        return 1;
    }
    return 0;
}

int checkLeft( int* mat,  int rows,  int cols,  int new_piece_index)
{
    int flag = (new_piece_index + 1) % cols;
    if (flag > 0)
    {
        return 1;
    }
    return 0;
}

void printMatrix(int* mat, int rows, int cols)
{
	for (int i = 0; i < rows; i++)
	{

		for (int j = 0; j < cols; j++)
		{
			printf("%5d", *(mat + (i * cols) + j));
		}
		printf("\n");
	}
}

int checkWin( int* mat,  int rows,  int cols)
{
	for (int i = 0; i < rows * cols - 1; i++)
	{
		if (*(mat + i) > *(mat + i + 1))
		{
			return 0;
		}
	}
	return 1;
}

int indexValue(int* mat, int size, int num)
{
	for (int i = 0; i < size; i++)
	{
		if (*(mat + i) == num)
		{
			return i;
		}
	}
	return -1;
}

void initializeMatrix(int* mat, int rows, int cols)
{
	int count = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++, count++)
		{
			*(mat + (i * cols) + j) = count;

		}
	}

}
