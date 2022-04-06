#ifndef __AIR_MANAGER__
#define __AIR_MANAGER__
#include <stdio.h>
#include "Airport.h"
#include "List.h"
typedef struct
{
	LIST arr;
	int			count;
}AirportManager;

int		 addAirport(AirportManager* pManager);
Airport* findAirportByCode(const AirportManager* pManager, const char* code);
void	printAllAirport(const AirportManager* pManager);
int		initManager(AirportManager* pManager);
void	freeManager(AirportManager* pManager);
void    setAirport(Airport* pPort, AirportManager* pManager);
void	createAirport(Airport* arr, int index);
int		checkUniqeCodetwo(const char* code, const AirportManager* pManager);
int	    initAirportManagerFromFile(AirportManager* pManager, const char* filename);
int	    saveDataTofile(AirportManager* pManager, const char* filename);
#endif