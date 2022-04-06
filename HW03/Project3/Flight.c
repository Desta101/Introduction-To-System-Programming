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
#include <stdlib.h>
#include <string.h>
#include "Flight.h"
#include "General.h"
#include "Date.h"

int		isFlightInRoute(const Flight* pFlight,const char* codeSource, const char* codeDest)
{
	if ((strcmp(pFlight->pOriginAirport, codeSource) == 0) &&
		(strcmp(pFlight->pDestAirport, codeDest) == 0))
		return 1;

	return 0;
}

int		countFlightsInRoute(Flight** arr, int size,const char* codeSource, 
		const char* codeDest)
{
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		if (isFlightInRoute(arr[i], codeSource, codeDest))
			count++;
	}
	return count;
}



void	printFlight(const Flight* pFlight)
{
		printf("Flight From %s To %s\n", pFlight->pOriginAirport, pFlight->pDestAirport);
		printDate(&pFlight->date);
		printf("Hour: %d \n", pFlight->hour);


}


void	initFlight(Flight* pFlight, const AirportManager* pManager)
{	
	char* str;
	getc(stdin);
	Airport* Aorigin = SearchAiport(pManager, "Enter code of origin airport:");
	strcpy(pFlight->pOriginAirport, Aorigin->code);
	int same;
	do {
		Airport* Adestination = SearchAiport(pManager, "Enter code of destination airport:");
		same = isSameAirport(Aorigin, Adestination);
		if(same)
			printf("Same origin and destination airport\n");
		else
			strcpy(pFlight->pDestAirport, Adestination->code);
	} while (same);
	str= getCorrectDate();
	//pFlight->date = (Date*)malloc(sizeof(Date));
	initDate(&pFlight->date, str);
	pFlight->hour = getFlightHour();
	
}
void	initFlightbycode(Flight* pFlight, const AirportManager* pManager,int num)
{

	char* str;
	getc(stdin);
	if (num == 1) {
		Airport* pPortOr = SearchAiport(pManager, "Enter code of origin airport:");
		strcpy(pFlight->pOriginAirport, pPortOr->code);
	}
		//setAiport(pManager,&pFlight->pOriginAirport, "Enter code of origin airport:");
	else {
		//setAiport(pManager, &*pFlight->pDestAirport, "Enter code of destination airport:");
		Airport* pPortOr = SearchAiport(pManager, "Enter code of origin airport:");
		strcpy(pFlight->pDestAirport, pPortOr->code);
	}
}

int getFlightHour()
{
	int h;
	do {
		printf("Enter flight hour [0-23]: ");
		scanf("%d", &h);
	} while (h < 0 || h>23);
	return h;
}



void	setAiport(const AirportManager* pManager, Airport** hAirport, const char* msg)
{
	char code[MAX_STR_LEN];
	Airport* port;
	do
	{
		printf("%s ", msg);
		myGets(code, MAX_STR_LEN,stdin);
		port = findAirportByCode(pManager, code);
		if (port == NULL)
			printf("No airport in this country - try again\n");
	} while(port == NULL);

	*hAirport = port;

}


void	freeFlight(Flight* pFlight)
{
	
	free(pFlight);
}
int comperHour(const void* f1, const void* f2) {

	Flight* a = *(Flight**)f1;
	Flight* b = *(Flight**)f2;
	return a->hour - b->hour;


}

int comperDate(const void* f1, const void* f2) {
	Flight* a = *(Flight**)f1;
	Flight* b = *(Flight**)f2;
	if (a->date.year > b->date.year)return 1;
	if(a->date.year < b->date.year)return -1;
	if (a->date.year == b->date.year)
	{
		if (a->date.month > b->date.month)return 1;
			
		if (a->date.month < b->date.month)return -1;
		else {
			if (a->date.day > b->date.day)return 1;
			if (a->date.day < b->date.day)return -1;
		}

	}
	return 0;



}
int compareDestenation(const void* o1, const void* o2)
{
	Flight* pFlight1 = *(Flight**)o1;
	Flight* pFlight2 = *(Flight**)o2;
	return strcmp(pFlight1->pDestAirport, pFlight2->pDestAirport);
}

int compareOrigin(const void* o1, const void* o2)
{
	Flight* pFlight1 = *(Flight**)o1;
	Flight* pFlight2 = *(Flight**)o2;
	return strcmp(pFlight1->pOriginAirport, pFlight2->pOriginAirport);
}



Airport* SearchAiport(const AirportManager* pManager, const char* msg)
{
	char code[MAX_STR_LEN];
	Airport* port;
	do
	{
		printf("%s\t", msg);
		myGets(code, MAX_STR_LEN, stdin);
		port = findAirportByCode(pManager, code);
		if (port == NULL)
			printf("No airport in this country - try again\n");
	} while (port == NULL);

	return port;

}


