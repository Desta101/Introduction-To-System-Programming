#pragma once
#include "General.h"
typedef struct
{
	int day;
	int month;
	int year;
}Date;


void printDate(const Date* date);
void initDate(Date* pDate, char* str);
int	 checkDate(char* date);
int  compareDate(const Date* date1, const Date* date2);
void printTheDate(const char* date);
