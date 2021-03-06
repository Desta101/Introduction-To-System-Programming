#pragma once
#include "Airport.h"

typedef struct {
	Airport* air;
	int num_of_aPorts;
}Airport_Manager;

//General
void print_airport_manager(void* air_man);
int add_airport(Airport_Manager* air_man);
int init_airport_manager(Airport_Manager* air_man);
int check_if_num(char* c, int size);