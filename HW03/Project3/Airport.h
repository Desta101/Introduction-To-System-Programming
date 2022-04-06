#ifndef __AIRPORT__
#define __AIRPORT__

#define CODE_LENGTH 3

typedef struct
{
	char*	name;
	char*	country;
	char	code[CODE_LENGTH+1];

}Airport;

int		isSameAirport(const Airport* pPort1, const Airport* pPort2);
int		isAirportCode(const Airport* pPort1, const char* code);
void	printAirport(const Airport* pPort);
void	initAirportNoCode(Airport* pPort);
void	initAirportCode(Airport* pPort);
void    getCode(char* code);
int		checkUniqeCode(const char* code, Airport* arr, int count);
void	getAirportName(Airport* pPort);
void	freeAirport(Airport* pPort);
double	toRad(double degree);
int		compareAirportsByCode(const Airport* pPort1, const Airport* pPort2);
int		readAirportDataFromFile(Airport* airport, FILE* file);
void	saveAirportDataFromFile(Airport* airport, FILE* file);
void	changeEvenWord(char* str);
void	getAirportNewName(Airport *pPort);



#endif