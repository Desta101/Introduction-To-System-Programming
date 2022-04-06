/*
 ============================================================================
 Name        : HW03.c
 Author      : Shimon desta 203670286 and Tal saar 209151380
 Copyright   : Your copyright notice
 Description : Airport Manager in C
 ============================================================================
*/
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#include "Airport.h"
#include "General.h"


int		isSameAirport(const Airport* pPort1, const Airport* pPort2)
{
	if (!pPort1 || !pPort2)
		return 0;
	if (strcmp(pPort1->code, pPort2->code) == 0)
		return 1;

	return 0;
}

int		isAirportCode(const Airport* pPort1, const char* code)
{
	if (!pPort1)
		return 0;
	if (strcmp(pPort1->code, code) == 0)
		return 1;

	return 0;


}
void	getAirportName(Airport* pPort)
{
	char temp[255];
	char** wordsArray = NULL;
	int totalLength;
	int count;

	printf("Enter airport name:");
	myGetsdate(temp, MAX_STR_LEN);

	wordsArray = splitCharsToWords(temp, &count, &totalLength);
	pPort->name = (char*)calloc(totalLength + (count - 1) * 2 + 1, sizeof(char));
	if (!pPort->name)
	{
		for (int i = 0; i < count; i++)
			free(wordsArray[i]);
		free(wordsArray);
		return;
	}
	int len;
	for (int i = 0; i < count; i++)
	{
		len = (int)strlen(wordsArray[i]);
		if (len % 2 == 0) //even number of letters
			changeEvenWord(wordsArray[i]);
		else {
			if (i == count - 1 && count > 1) //last but not only!
				wordsArray[i][0] = tolower(wordsArray[i][0]); //small
			else
				wordsArray[i][0] = toupper(wordsArray[i][0]); //big
		}
		strcat(pPort->name, wordsArray[i]);
		if (i != count - 1) //not last
			strcat(pPort->name, "  ");
	}

	//clean temp data
	for (int i = 0; i < count; i++)
		free(wordsArray[i]);
	free(wordsArray);
}

void	changeEvenWord(char* str)
{
	while (*str)
	{
		*str = toupper(*str);
		str++;
		*str = tolower(*str);
		str++;
	}
}





void	printAirport(const Airport* pPort)
{
	
	printf("Airport name:%s\n", pPort->name);
	printf("Country: %s\n",pPort->country);
	printf("Code:%s\n\n", pPort->code);
}
void	initAirportNoCode(Airport* pPort)
{
	getAirportName(pPort);
	pPort->country = getStrExactName("Enter airport country");

}


void	initAirportCode(Airport* pPort)
{
	getCode(pPort->code);
}
int compareAirportsByCode(const Airport* pPort1, const Airport* pPort2)
{
	return strcmp(pPort1->code, pPort2->code);
}
void getCode(char* code)
{
	char temp[MAX_STR_LEN];
	int ok = 1;
	do {
		ok = 1;
		printf("Enter airport code  - %d letters:",CODE_LENGTH);
		myGets(temp, MAX_STR_LEN,stdin);
		if (strlen(temp) != CODE_LENGTH)
		{
			printf("code should be %d letters:\n",CODE_LENGTH);
			ok = 0;
		}
		else {
			for (int i = 0; i < 3; i++)
			{
				if (isupper(temp[i]) == 0)
				{
					printf("Need to be upper case letter:\n");
					ok = 0;
					break;
				}
			}
		}
	} while (!ok);

	strcpy(code, temp);
}



int checkUniqeCode(const char* code, Airport* arr, int count)
{
	for (int i = 0; i < count; i++)
	{
		if (strcmp(code, arr[i].code) == 0)
			return 0;
	}
	return 1;
}



void	freeAirport(Airport* pPort)
{
	free(pPort->name);
	free(pPort->country);
	
}

double	toRad(double degree)
{
	return (degree*M_PI) / 180;
}
int readAirportDataFromFile(Airport* airport, FILE* file) {

	airport->name = getStrExactLength(file);
	//getAirportNewName(airport);
	if (strlen(airport->name) == 0)
	{
		airport->name = getStrExactLength(file);
		//getAirportNewName(airport, airport->name);
	}
	airport->country = getStrExactLength(file);
	int res = fscanf(file, "%s", airport->code);
	if (res == 1)
		return 1;

	return 0;


}

void saveAirportDataFromFile(Airport* airport, FILE* file) {
	
	//printf( "%s\n%s\n%s\n", airport->name, airport->country, airport->code);
	fprintf(file, "%s\n%s\n%s\n", airport->name, airport->country, airport->code);
	

}
void	getAirportNewName(Airport *pPort)
{
	char temp[255];
	char** wordsArray = NULL;
	int totalLength;
	int count;
	
	strcpy(temp, pPort->name);

	wordsArray = splitCharsToWords(temp, &count, &totalLength);
	pPort->name = NULL;
	pPort->name = (char*)calloc(totalLength + (count - 1) * 2 + 1, sizeof(char));
	if (!pPort->name)
	{
		for (int i = 0; i < count; i++)
			free(wordsArray[i]);
		free(wordsArray);
		return;
	}
	int len;
	for (int i = 0; i < count; i++)
	{
		len = (int)strlen(wordsArray[i]);
		if (len % 2 == 0) //even number of letters
			changeEvenWord(wordsArray[i]);
		else {
			if (i == count - 1 && count > 1) //last but not only!
				wordsArray[i][0] = tolower(wordsArray[i][0]); //small
			else
				wordsArray[i][0] = toupper(wordsArray[i][0]); //big
		}
		strcat(pPort->name, wordsArray[i]);
		if (i != count - 1) //not last
			strcat(pPort->name, "  ");
	}
	printf("%s", pPort->name);
	//clean temp data
	for (int i = 0; i < count; i++)
		free(wordsArray[i]);
	free(wordsArray);
}


