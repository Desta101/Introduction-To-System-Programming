#include <stdio.h>
#include <stdlib.h>
#include "../headers/main.h"
#include "../headers/PictureManipulation.h"
#include "../headers/NumberGame.h"

int main()
{
    printf("Welcome to the program\n");
	char temp = '\0';
    while (temp != 'e')
    {
        printf("Please choose one of the following options\n");
        printf("P/p - Picture Manipulation\n");
        printf("N/n - Number Game\n");
        printf("E/e - Quit\n");
        scanf("%c", &temp);
        switch (temp)
        {
            case 'p':
            case 'P':
				PictureManipulation();
                break;
            case 'n':
            case 'N':
				NumberGame();
                break;
            case 'e':
            case 'E':
                printf("Bye Bye\n");
                exit(0);
            default:
                printf("Please choose a valid option\n");
                break;
        }
    }
	return 0;
}


