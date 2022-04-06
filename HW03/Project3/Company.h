#ifndef __COMP__
#define __COMP__

#include "Flight.h"
#include "AirportManager.h"
typedef enum {
	Hoursort, Datesort, Origin, Destenation,none
} sorttype;
typedef struct
{
	char*		name;
	int			planeCount;
	int			flightCount;
	Flight**	flightArr;
	LIST		allDates;
	sorttype sortedtyped;
}Company;


int		addFlight(Company* pComp,const AirportManager* pManager);

void	printCompany( Company* pComp);
void	printFlightsCount(const Company* pComp);
void	initCompany(Company* pComp);
void	deleteCompany(Company* pComp);
void	printFlightArr(Flight** pFlight, int size);
void	freeFlightArr(Flight** arr, int size);
int	    initAirportLineFromFile(Company* pCompany, const char* file, AirportManager* pAirportManager);
int     saveAirportLineFromFile(Company* airline, const char* file);
void	freeCompany(Company* pComp);
void    sortingbeforprinting(Company* airline);
void    SearchFlight(Company* ailrline, AirportManager* pPort);
void addAlldates(Company* pCompany, int size);
void addinfo(Company* pCompany, int i, FILE *fp);
#endif

