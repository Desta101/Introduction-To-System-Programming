#include "AirportManager.h"
//adding airport
int add_airport(Airport_Manager* air_man)
{
	air_man->air = (Airport*)realloc(air_man->air, sizeof(Airport) * (air_man->num_of_aPorts + 1));
	if (!air_man->air)
		return 0;
	if (get_airport_from_user(air_man->air, air_man->num_of_aPorts) == 0)
		return 0;
	air_man->num_of_aPorts += 1;
	return 1;
}

//checking if inserted string has a numeric value
int check_if_num(char* c, int size)
{
	int i;
	for (i = 0; i < size; i++)
		if (isdigit(*(c + i)) == 0)
			return 0;
	return 1;
}
//initializing airport manager 
int init_airport_manager(Airport_Manager* air_man)
{
	int i, amount, bool = 0, len;
	char c[MAX_LEN];
	char* str = NULL;
	printf("Enter amount of airports:\n");
	scanf("%s", &c);
	str = _strdup(c);
	len = strlen(str);
	while (!bool)
	{
		if (check_if_num(str, len) == 0)
		{
			printf("Error! Please enter numbers only...\n");
			printf("Enter amount of airports:\n");
			scanf("%s", &c);
			str = _strdup(c);
			len = strlen(str);
		}
		else
		{
			amount = atoi(str);
			bool = 1;
		}
	}
	air_man->num_of_aPorts = amount;
	air_man->air = (Airport*)malloc(sizeof(Airport) * amount);
	for (i = 0; i < amount; i++)
		if (get_airport_from_user(air_man->air, i) == 0)
			return 0;
	return 1;
}
//printing airport manager
void print_airport_manager(void* air_man)
{
	Airport_Manager* air = (Airport_Manager*)air_man;
	int i;
	printf("Number of airports in the program = %d\n", air->num_of_aPorts);
	for (i = 0; i < air->num_of_aPorts; i++)
	{
		printf("---------------------Airport %d---------------------\n", i + 1);
		printf("Airport name:%s\n", air->air[i].name);
		printf("Airport country:%s\n", air->air[i].country);
		printf("Airport IATA:%s\n", air->air[i].IATA);
	}
}
