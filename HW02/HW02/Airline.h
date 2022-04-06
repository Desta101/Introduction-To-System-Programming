#define _CRT_SECURE_NO_WARNINGS
#include "Flight.h"
#define BY_TIME 1
#define BY_DATE 2

typedef enum { by_time, by_date }sort_type;

typedef struct {
	char* name;
	int num_of_planes;
	int num_of_flights;//Assume start with 0
	Flight** flight;
	sort_type the_type;
}Airline;

//Check
int is_valid_date(int dd, int mm, int yy, Date* date);
int is_valid_flight_time(int* num);
int is_origin_dest_valid(const Airport_Manager* air_man, int* pos1, int* pos2);


//General
int init_airline(Airline* airline);
int init_flights(Airline* airline, Airport_Manager* air_man, FILE* fp);
void print_airline(Airline* airline);
void print_flights_in_line(Airline* airline);
void print_specific_flight(Flight* the_flight);
void take_off(Flight* flights, ...);

//Sort Compare & Search

int compare_by_date(const void* fl1, const void* fl2);
int compare_by_time(const void* fl1, const void* fl2);
int mini_menu(int indicator);
void sort_arr(Airline* airline);
void search_flight(Airline* airline);

//Utils
int add_flight(Airline* airline, const Airport_Manager* air_man);
int get_flight_from_user(Airline* airline, const Airport_Manager* air_man);
int get_date(Date* date);
int get_origin_iata(const Airport_Manager* air_man);
int get_dest_iata(const Airport_Manager* air_man);
Airport* get_airport(Airport_Manager* air_man, char* code);
void free_airline(void* airline);
void free_airport(void* air_man);
