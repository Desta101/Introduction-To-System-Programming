#include "../headers/PictureManipulation.h"
#include "../headers/NumberGame.h"


void PictureManipulation()
{
	int opn = 0;
	int rows = ROWS, cols = COLS;
	int matP[3][3];
	matrixRandom((int*)matP, rows, cols, 1, 100);
	printf("\n\n");
	printMatrix((int*)matP, rows, cols);
	while (opn != -1)
	{
		printf("Please choose one of the following options\n");
		printf("1 - 90 degree clockwise\n");
		printf("2 - 90 degree counter clock wise\n");
		printf("3 - Flip Horizontal\n");
		printf("4 - Flip Vertical\n");
		printf("- 1 - Quit\n");
		scanf("%d", &opn);
		switch (opn)
		{
		case 1:
			printf("\n\n");
			printMatrix((int*)matP, rows, cols);
			nintyDegreeForward((int*)matP, rows, cols);
			printf("--------------- Picture after manipulation ---------------\n\n");
			printMatrix((int*)matP, rows, cols);
			printf("\n");
			break;
			break;
		case 2:
			printf("\n\n");
			printMatrix((int*)matP, rows, cols);
			nintyDegreeBack((int*)matP, rows, cols);
			printf("--------------- Picture after manipulation ---------------\n\n");
			printMatrix((int*)matP, rows, cols);
			printf("\n");
			break;
		case 3:
			printf("\n\n");
			printMatrix((int*)matP, rows, cols);
			horizontally((int*)matP, rows, cols);
			printf("--------------- Picture after manipulation ---------------\n\n");
			printMatrix((int*)matP, rows, cols);
			printf("\n");
			break;
		case 4:
			printf("\n\n");
			printMatrix((int*)matP, rows, cols);
			vertically((int*)matP, rows, cols);
			printf("--------------- Picture after manipulation ---------------\n\n");
			printMatrix((int*)matP, rows, cols);
			printf("\n\n");
			break;
		case -1:
			printf("Bye Bye\n");
			exit(0);
		default:
			printf("Please choose a valid option\n");
			break;
		}
	}
}

void matrixRandom(int* mat, int rows, int cols, int from_num, int to_num){

	for (int i = 0; i < rows; i++){
		for (int j = 0; j < cols; j++)
		{
			*(mat + (i * cols) + j) = (rand() % (to_num - from_num + 1)) + from_num;
		}
	}
}
void nintyDegreeForward(int* mat,  int rows,  int cols)
{
    nintyDegreeForwardRotate(mat, mat + (rows * cols) - 1, rows, cols, cols);
}

void vertically(int* mat, int rows, int cols)
{
	verticallyFlip(mat, mat + (cols - 1), cols, cols);
}
void nintyDegreeBack(int* mat, int rows, int cols)
{
	nintyDegreeBackRotate(mat, mat + (rows * cols) - 1, rows, cols, cols);
}
void horizontally(int* mat, int rows, int cols)
{
	HorizontalFlip(mat, mat + (rows * (cols - 1)), cols, rows);
}


void nintyDegreeForwardRotate(int* start, int* end,  int rows,  int cols,  int coltwo)
{
    if (rows <= 1 && cols <= 1)
    {
        return;
    }
    else{
        int* temp1 = start, *temp2 = start + (cols - 1), *temp3 = end, *temp4 = end - (cols - 1);
        for (int i = 0; i < rows - 1; i++, temp1++, temp2 += coltwo, temp3--, temp4 -= coltwo){
            int temp = *(temp1);
            *(temp1) = *(temp4);
            *(temp4) = *(temp3);
            *(temp3) = *(temp2);
            *(temp2) = temp;
        }
        nintyDegreeForwardRotate(start + cols + 1, end - (cols + 1), rows - 2, cols - 2, cols);
    }
}

void nintyDegreeBackRotate(int* start, int* end,  int rows,  int cols,  int coltwo)
{
    if (rows <= 1 && cols <= 1)
    {
        return;
    }
    else{
        int* temp1 = start, *temp2 = start + (cols - 1), *temp3 = end, *temp4 = end - (cols - 1);
        for (int i = 0; i < rows - 1; i++, temp1++, temp2 += coltwo, temp3--, temp4 -= coltwo) {
            int temp = *(temp1);
            *(temp1) = *(temp2);
            *(temp2) = *(temp3);
            *(temp3) = *(temp4);
            *(temp4) = temp;
        }
        nintyDegreeBackRotate(start + cols + 1, end - (cols + 1), rows - 2, cols - 2, cols);
    }
}

void HorizontalFlip(int* start, int* end,  int coltwo,  int rows)
{
    if (rows <= 1)
    {
        return;
    }
    else{
        int* temp1 = start, *temp2 = end;
        for (int i = 0; i < coltwo; i++, temp1++, temp2++){
            int temp = *(temp1);
            *(temp1) = *(temp2);
            *(temp2) = temp;
        }
        HorizontalFlip(start + coltwo, end - coltwo, coltwo, rows - 2);
    }
}

void verticallyFlip(int* start, int* end,  int coltwo, int cols)
{
    if (cols <= 1)
    {
        return;
    }
    else {
        int* temp1 = start, *temp2 = end;
        for (int i = 0; i < coltwo; i++, temp1 += coltwo, temp2 += coltwo){
            int temp = *(temp1);
            *(temp1) = *(temp2);
            *(temp2) = temp;
        }
        verticallyFlip(start + 1, end - 1, coltwo, cols - 2);
    }
}
