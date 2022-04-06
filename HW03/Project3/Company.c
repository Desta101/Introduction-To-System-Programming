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
#include "Company.h"
#include "Airport.h"
#include "General.h"
#include "Date.h"


int		addFlight(Company* pCompany,const AirportManager* pManager)
{
	pCompany->flightArr = (Flight**)realloc(pCompany->flightArr, (pCompany->flightCount+1) * sizeof(Flight*));
	if (!pCompany->flightArr)
		return 0;
	pCompany->flightArr[pCompany->flightCount] = (Flight*)calloc(1,sizeof(Flight));
	if (!pCompany->flightArr[pCompany->flightCount])
		return 0;
	initFlight(pCompany->flightArr[pCompany->flightCount],pManager);
	pCompany->flightCount++;

	if (pCompany->flightCount > 1)
	{
		for (int i = 0; i < pCompany->flightCount - 1; i++)
		{
			if (compareDate(&pCompany->flightArr[pCompany->flightCount - 1]->date, &pCompany->flightArr[i]->date) == 0)
				return 1;
		}
	}
	char Str[MAX_STR_LEN];
	sprintf(Str, "%d/%d/%d", pCompany->flightArr[pCompany->flightCount - 1]->date);
	insertList(&pCompany->allDates.head, getDynStr(Str));
	return 1;
}

void	printCompany(Company* pCompany)
{
	
	printf("Company %s:\n", pCompany->name);
	printf("Has %d planes and %d flights:\n", pCompany->planeCount, pCompany->flightCount);
	printFlightArr(pCompany->flightArr, pCompany->flightCount);
	if (pCompany->flightCount != 0) {
		printf("---ALL Dates---\n");
		printList(&pCompany->allDates, printTheDate);
	}
}

void	printFlightsCount(const Company* pCompany)
{
	char codeOrigin[CODE_LENGTH+1];
	char codeDestination[CODE_LENGTH + 1];
	
	if (pCompany->flightCount == 0)
	{
		printf("No flight to search\n");
		return;
	}
	getc(stdin); //clean buffer
	printf("Origin Airport\n");
	getCode(codeOrigin);
	printf("Destination Airport\n");
	getCode(codeDestination);
	int count = countFlightsInRoute(pCompany->flightArr, pCompany->flightCount, codeOrigin, codeDestination);
	if (count != 0)
		printf("There are %d flights ", count);
	else
		printf("There are No flights ");

	printf("----- From %s to %s ----\n",codeOrigin, codeDestination);
}

void	initCompany(Company* pCompany)
{
	fflush(stdin);
	getchar();
	pCompany->name = getStrExactName("Enter company name");
	printf("Enter plane count:");
	scanf("%d", &pCompany->planeCount);
	pCompany->flightArr = NULL;
	pCompany->flightCount = 0;
	initList(&pCompany->allDates);
}

void	deleteCompany(Company* pCompany)
{
	free(pCompany->name);
	free(pCompany->flightArr);
}

void	printFlightArr(Flight** pFlight, int size)
{
	generalArrayFunction(pFlight, size, sizeof(Flight*), printFlight);
	//for (int i = 0; i < size; i++)
	//	printFlight(pFlight[i]);
}

void	freeFlightArr(Flight** pFlight, int size)
{
	for (int i = 0; i < size; i++)
	{
		freeFlight(pFlight[i]);
	}
	//generalArrayFunction(arr,size, sizeof(Flight*), freeFlight);
}
void	freeCompany(Company* pCompany)
{
	freeFlightArr(pCompany->flightArr, pCompany->flightCount);
	free(pCompany->flightArr);
	free(pCompany->name);
}

int initAirportLineFromFile(Company* pCompany, const char* file,AirportManager * pAirportManager) {
	FILE* fp = fopen(file, "rb");
	if (!fp)
		return 0;
	char code[4];
	int size;
	fread(&pCompany->planeCount, sizeof(int), 1, fp);
	fread(&size, sizeof(int), 1, fp);
	pCompany->name = (char*)malloc((size + 1) * sizeof(char));
	fread(pCompany->name, sizeof(char), size, fp);
	pCompany->name[size] = '\0';
	fread(&pCompany->flightCount, sizeof(int), 1, fp);
	if (pCompany->flightCount < 0)
		pCompany->flightCount = 0;
	pCompany->flightArr = (Flight**)malloc(pCompany->flightCount * sizeof(Flight*));
	if (!pCompany->flightArr)
		return 0;
	fread(&pCompany->sortedtyped, sizeof(sorttype), 1, fp);
	initList(&pCompany->allDates);
	for (int i = 0; i < pCompany->flightCount; i++) {
		addinfo(pCompany, i,fp);
	}
	addAlldates(pCompany, pCompany->flightCount);
	fclose(fp);
	return 1;
}
void addinfo(Company* pCompany, int i,FILE *fp) {
	pCompany->flightArr[i] = (Flight*)malloc(sizeof(Flight));
	fread(&pCompany->flightArr[i]->pOriginAirport, sizeof(char), 3, fp);
	pCompany->flightArr[i]->pOriginAirport[3] = '\0';
	fread(&pCompany->flightArr[i]->pDestAirport, sizeof(char), 3, fp);
	pCompany->flightArr[i]->pDestAirport[3] = '\0';
	fread(&(pCompany->flightArr[i]->hour), sizeof(int), 1, fp);
	fread(&pCompany->flightArr[i]->date, sizeof(Date), 1, fp);
}


void addAlldates(Company* pCompany, int size) {
	char str[MAX_STR_LEN];
	int count = 0;
	if (size == 1) {
		sprintf(str, "%d/%d/%d", pCompany->flightArr[size - 1]->date);
		insertList(&pCompany->allDates.head, getDynStr(str));

	}
	else {
		for (int i = 0; i < pCompany->flightCount; i++) {
			for (int j = 0; j < i; j++) {
				if (compareDate(&pCompany->flightArr[i]->date, &pCompany->flightArr[j]->date) != 0)
					count++;
			}
			if (count == i) {
				sprintf(str, "%d/%d/%d", pCompany->flightArr[i]->date);
				insertList(&pCompany->allDates.head, getDynStr(str));
			}
			count = 0;
		}

	}
}






int saveAirportLineFromFile(Company* airline, const char* file) {
	FILE* fp;
	int nameSize;
	fp = fopen(file, "wb");
	if (!fp)
		return -1;
	nameSize = (int)strlen(airline->name);
	fwrite(&airline->planeCount, sizeof(int), 1, fp);
	fwrite(&nameSize, sizeof(int), 1, fp);
	fwrite(airline->name, sizeof(char), nameSize, fp);
	fwrite(&airline->flightCount, sizeof(int), 1, fp);
	fwrite(&airline->sortedtyped, sizeof(sorttype), 1, fp);
	for (int i = 0; i < airline->flightCount; i++) {
		fwrite(airline->flightArr[i]->pOriginAirport, sizeof(char), strlen(airline->flightArr[i]->pOriginAirport), fp);
		fwrite(airline->flightArr[i]->pDestAirport, sizeof(char), strlen(airline->flightArr[i]->pDestAirport), fp);
		fwrite(&(airline->flightArr[i]->hour), sizeof(int), 1, fp);
		fwrite(&(airline->flightArr[i]->date), sizeof(Date), 1, fp);
		
	}
	fclose(fp);
	freeList(&airline->allDates, free);
	return 1;

}

void Chosingtypeofsorting(Company* airline) {
	if (airline->flightCount == 0)
	{
		printf("There are no flight yet So...please add flight (Press 0) in order to sort\n");
		return;
	}
	printf("Please enter sort type\n");
	printf("1 for by hour \n");
	printf("2 for by date \n");
	printf("3 for by Origin \n");
	printf("4 for by Destenation \n");
	printf("every number for no sorting: \n");
	int option = 0;
	scanf("%d", &option);
	switch (option) {
	case 1:
		airline->sortedtyped = Hoursort;
		break;
	case 2:
		airline->sortedtyped = Datesort;
		break;
	case 3:
		airline->sortedtyped = Origin;
		break;
	case 4:
		airline->sortedtyped = Destenation;
		break;
	default:
		airline->sortedtyped = none;
		break;


	}
}
void sortingbeforprinting( Company* airline) {
	Chosingtypeofsorting (airline);
	switch (airline->sortedtyped) {

	case Hoursort:
		qsort(airline->flightArr, airline->flightCount, sizeof(Flight*), comperHour);
		break;
	case Datesort:
		qsort(airline->flightArr, airline->flightCount, sizeof(Flight*), comperDate);
		break;
	case Origin:
		qsort(airline->flightArr, airline->flightCount, sizeof(Flight*), compareOrigin);
		break;
	case Destenation:
		qsort(airline->flightArr, airline->flightCount, sizeof(Flight*), compareDestenation);
		break;
	case none:
		break;
	}
	
}
void SearchFlight(Company* airline, AirportManager* pPort) {
	if (airline->sortedtyped == none)
	{
		printf("----Error:You need first to sort the flights in the Array first----\n\t\t\tSo press 5!\t\n");
		return;
	}
	int (*compareFunction)(const void*, const void*) = NULL;
	Flight* flightToFind = (Flight*)malloc(sizeof(Flight));
	
	
	switch (airline->sortedtyped)
	{
	case Hoursort:
		printf("------------Search Flights by Hour----------\n");
		compareFunction = comperHour;
		printf("Enter hour of flight:\n");
		scanf("%d", &flightToFind->hour);
		break;
	case Datesort:
		printf("----------Search Flights by Date------------\n");
		compareFunction = comperDate;
		getchar();
		char* str = getCorrectDate();
		initDate(&(flightToFind->date), str);
		break;
	case Origin:
		printf("----------Search Flights by Origin----------\n");
		compareFunction = compareOrigin;
		if (!flightToFind)
		{
			printf("problem loading flight\n");
			return;
		}
		initFlightbycode(&(flightToFind->pOriginAirport), pPort,1);
		break;
	case Destenation:
		printf("--------Search Flights by Destenation-------\n");
		compareFunction = compareDestenation;
		if (!flightToFind)
		{
			printf("problem loading flight\n");
			return;
		}
		initFlightbycode(&(flightToFind->pOriginAirport), pPort,0);//yes the Search Flights by Origin not the Destenation
		break;
	
	default:
		printf("Sort the flights in the company first So.. Press 5)\n");
		return;
	}
	Flight** flight = bsearch(&flightToFind, airline->flightArr, airline->flightCount, sizeof(Flight*), compareFunction);
	if (!flight)
		printf("Flight not found\n");
	else {
	
		printf("-----------------Your Flight:---------------\n");
		printFlight(*flight);
	}
	freeFlight(flightToFind);
	
}


	




