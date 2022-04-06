/*
 ============================================================================
 Name        : HW03.c
 Author      : Shimon desta 203670286 and Tal saar 209151380
 Copyright   : Your copyright notice
 Description : Airport Manager in C
 ============================================================================
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Date.h"
#include "Airport.h"
#include "General.h"
#include "Company.h"
#define TEMP_BUFFER_SIZE 50

char* getStrExactstrfromFile( FILE* f)
{

	char* str;
	char temp[MAX_STR_LEN];
	myGets(temp, MAX_STR_LEN,f);
	str = getDynStr(temp);
	printf("the str is %s\n", str);
	return str;
}

char* getStrExactName(const char* msg)
{
	char* str;
	char temp[MAX_STR_LEN];
	printf("%s:", msg);
	myGets(temp, MAX_STR_LEN,stdin);

	str = getDynStr(temp);
	return str;
}

char* getDynStr(char* str)
{
	char* theStr;
	theStr = (char*)malloc((strlen(str) + 1) * sizeof(char));
	if (!theStr)
		return NULL;

	strcpy(theStr, str);
	return theStr;
}


char* getCorrectDate()
{

	char* str;
	char date[MAX_STR_LEN];
	int ok = 1;
	
	do {
		printf("Enter Flight Date dd/mm/yyyy: ");
		myGetsdate(date, MAX_STR_LEN);
		ok = checkDate(date);
		if (!ok)
			printf("Error try again\n");
	} while (!ok);

	str = (char*)malloc((strlen(date) + 1) * sizeof(char));
	if (!str)
		return NULL;

	strcpy(str, date);
	return str;
}



double getDoubleCheckLimits(const char* msg, double start, double end)
{
	double val;
	do {
		printf("%s number should be between %.2lf and %.2lf including\n", msg, start, end);
		scanf("%lf", &val);
		if (val < start || val > end)
			printf("error in number, try again\n");
	} while (val < start || val > end);

	return val;
}


void generalArrayFunction(void* arr, int length, int size, void (*f)(void*))
{
	
	Flight** arrFlights = (Flight**)arr;
	for (int i = 0; i < length; i++)
	{
		f(arrFlights[i]);
	}
}

char* getStrExactLength(FILE* source)
{
	char temp[TEMP_BUFFER_SIZE]; 
	myGets(temp, TEMP_BUFFER_SIZE, source);
	//getAirportNewName(&temp);
	return _strdup(temp);
	
}
char* myGets(char* buffer, int size, FILE* f)
{
	if (buffer != NULL && size > 0)
	{
		if (fgets(buffer, size, f))
		{
			buffer[strcspn(buffer, "\n")] = '\0';
			return buffer;
		}
		*buffer = '\0';
	}
	return NULL;
}

char* myGetsdate(char* buffer, int size)
{
	if (buffer != NULL && size > 0)
	{
		if (fgets(buffer, size, stdin))
		{
			buffer[strcspn(buffer, "\n")] = '\0';
			return buffer;
		}
		buffer[0] = '\0';
	}
	return NULL;
}

char**	splitCharsToWords(char* str, int* pCount, int* pTotalLength)
{
	char temp[255];
	char* delimiters = " ";
	char* word;
	int count = 0;

	strcpy(temp, str);
	char** wordsArray = NULL;
	*pTotalLength = 0;

	word = strtok(temp, delimiters);
	while (word != NULL)
	{
		wordsArray = (char**)realloc(wordsArray, (count + 1) * sizeof(char*));
		if (!wordsArray)
			return 0;
		wordsArray[count] = getDynStr(word);
		count++;
		*pTotalLength += (int)strlen(word);
		word = strtok(NULL, delimiters);
	}
	*pCount = count;
	return wordsArray;
}
