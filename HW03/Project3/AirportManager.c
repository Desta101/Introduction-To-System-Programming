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
#include <stdlib.h>
#include <string.h>
#include "General.h"
#include "AirportManager.h"

int	initManager(AirportManager* pManager)
{
	pManager->count = 0;
	initList(&pManager->arr);
	int count = 0;
	do {
		printf("How many airport? ");
		scanf("%d", &pManager->count);
	} while (pManager->count < 1);

	if (count == 0)
	return 1;
	Airport* Arr = (Airport*)malloc(count * sizeof(Airport));
	if (Arr == NULL)
		return 0;
	for (int i = 0; i < pManager->count; i++)
	{	
		//createAirport(pManager->arr, i);
		setAirport(&Arr[i], pManager);
		if (SortInsertList(&pManager->arr.head, &Arr[i], compareAirportsByCode) == NULL)
			return 0;
	}
	//clean buffer
	
	char tav;
	scanf("%c", &tav);
	return 1;
}

Airport* findAirportByCode(const AirportManager* pManager, const char* code)
{
	/*
	for (int i = 0; i < pManager->count; i++)
	{
		if (isAirportCode(&pManager->arr[i], code))
			return &pManager->arr[i];
	}
	return NULL;

	*/
	if (&pManager->arr == NULL)
		return NULL;

	NODE* Arr;
	if (pManager->arr.head.next == NULL)
		return NULL;

	Arr = pManager->arr.head.next;
	while (Arr != NULL)
	{
		if (isAirportCode(Arr->key, code))
			return Arr->key;

		Arr = Arr->next;
	}

	return NULL;
}

void	printAllAirport(const AirportManager* pManager)
{
	printf("--------There are %d airports-------\n", pManager->count);
	printList(&pManager->arr, printAirport);
}



void  createAirport(Airport* arr, int index)
{
	//clean buffer
	char tav;
	scanf("%c", &tav);
	while(1)
	{
		initAirportCode(&arr[index]);
		if (checkUniqeCode(arr[index].code, arr, index))
			break;

		printf("This code already in use - enter a different code\n");
	}
	
	initAirportNoCode(&arr[index]);

}

int	addAirport(AirportManager* pManager)
{
	getchar();
	Airport* airport = (Airport*)malloc(1 * sizeof(Airport));
	setAirport(airport, pManager);
	if (SortInsertList(&pManager->arr.head, airport, compareAirportsByCode) != NULL)
	{
		pManager->count++;
		return 1;
	}
	return 0;
}



void freeManager(AirportManager* pManager)
{
	freeList(&pManager->arr, freeAirport);
}

int initAirportManagerFromFile(AirportManager* pManager, const char* filename) {
	FILE* f = fopen(filename, "r");
	if (!f) {
		return 0;
	}
	int res = fscanf(f, "%d", &pManager->count);
	if (res != 1)
		return 0;

	initList(&pManager->arr);
	char clean = 'a';
	fscanf(f, "%c", &clean);
	if (f == NULL)
		return 0;
	int count = (pManager->count);
	fscanf(f, "%d", &count);
	Airport* helper = (Airport*)malloc(pManager->count * sizeof(Airport));
	if (helper == NULL)
		return 0;
	for (int i = 0; i < count; i++)
	{
		int result = readAirportDataFromFile(&helper[i], f);
		if (!result)
			return 0;
		if (SortInsertList(&pManager->arr.head, &helper[i], compareAirportsByCode) == NULL)
			return 0;

		
	}

	fclose(f);
	return 1;
}

int saveDataTofile(AirportManager* pManager, const char* filename)
{
	FILE* f = fopen(filename, "w");
	
	if (f == NULL)
	{
		printf("Failed opening the file. Exiting!\n");
		return 0;
	}
	int count = (pManager->count);
	fprintf(f, "%d\n", count);

	saveAirportDataToFileList(&pManager->arr, saveAirportDataFromFile, f);

	fclose(f);

	return 1;

}

void  setAirport(Airport* pPort, AirportManager* pManager)
{
	while (1)
	{
		getCode(pPort->code);
		if (checkUniqeCodetwo(pPort->code, pManager))
			break;

		printf("This code already in use - enter a different code\n");
	}

	initAirportNoCode(pPort);
}
int checkUniqeCodetwo(const char* code, const AirportManager* pManager)
{
	Airport* port = findAirportByCode(pManager, code);

	if (port != NULL)
		return 0;

	return 1;
}



