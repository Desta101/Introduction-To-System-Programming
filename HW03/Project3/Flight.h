#ifndef __FLIGHT__
#define __FLIGHT__

#include "Airport.h"
#include "AirportManager.h"
#include "Date.h"
#include "Airport.h"
typedef struct
{
	char		pOriginAirport[CODE_LENGTH + 1];
	char		pDestAirport[CODE_LENGTH + 1];
	int			hour;
	Date		date; //dd/mm/yyyy
	
}Flight;



int		isFlightInRoute(const Flight* pFlight, const char* codeSource, const char* codeDest);
int		countFlightsInRoute(Flight** arr, int size,const char* codeSource, const char* codeDest);
void	printFlight(const Flight* pFlight);
void	initFlight(Flight* pFlight,const AirportManager* pManager);
int		getFlightHour();
void	setAiport(const AirportManager* pManager,Airport** hAirport, const char* msg);
void	initFlightbycode(Flight* pFlight, const AirportManager* pManager,int num);
void	freeFlight(Flight* pFlight);
int		comperHour(const void* f1, const void* f2);
int		comperDate(const void* f1, const void* f2);
int		compareOrigin(const void* o1, const void* o2);
int		compareDestenation(const void* o1, const void* o2);

Airport* SearchAiport(const AirportManager* pManager, const char* msg);




#endif
