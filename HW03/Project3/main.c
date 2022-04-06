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
#include "Company.h"
#include "AirportManager.h"
#include "General.h"
#define READFILENAME "airport_authority.txt"
#define ComapnyINIt "company.bin"
typedef enum
{ 
	eAddFlight, eAddAirport, ePrintCompany, ePrintAirports,
	ePrintFlightOrigDest, SortingflightArray,searchflight, eNofOptions
} eMenuOptions;

const char* str[eNofOptions] = { "Add Flight", "Add Airport",
								"PrintCompany", "Print all Airports",
								"Print flights between origin-destination","sorting flights array ","Search flight"};

#define EXIT			-1
int menu();

int main()
{
	AirportManager	manager;
	Company			company;

	if (!initAirportManagerFromFile(&manager, READFILENAME))
		initManager(&manager);
	if (!initAirportLineFromFile(&company,  ComapnyINIt, &manager))
		initCompany(&company);
	
	
	
	int option;
	int stop = 0;
	
	do
	{
		option = menu();
		switch (option)
		{
		case eAddFlight:
			if (!addFlight(&company, &manager))
				printf("Error adding flight\n");
			break;


		case eAddAirport:
			if (!addAirport(&manager))
				printf("Error adding airport\n");
			break;

		case ePrintCompany:
			printCompany(&company);
			break;

		case ePrintAirports:
			printAllAirport(&manager);
			break;

		case ePrintFlightOrigDest:
			printFlightsCount(&company);
			break;
		case SortingflightArray:

			sortingbeforprinting(&company);
			break;
		case searchflight:
			SearchFlight(&company, &manager);
			break;


		case EXIT:
			printf("Bye bye\n");
			stop = 1;
			break;

		default:
			printf("Wrong option\n");
			break;
		}
	} while (!stop);
	saveDataTofile(&manager, READFILENAME);
	saveAirportLineFromFile(&company, ComapnyINIt);
	freeManager(&manager);
	freeCompany(&company);
	
	return 1;
}

int menu()
{
	int option;
	printf("\n\n");
	printf("Please choose one of the following options\n");
	for(int i = 0 ; i < eNofOptions ; i++)
		printf("%d - %s\n",i,str[i]);
	printf("%d - Quit\n", EXIT);
	scanf("%d", &option);
	//clean buffer
	//char tav;
	//scanf("%c", &tav);
	return option;
}

