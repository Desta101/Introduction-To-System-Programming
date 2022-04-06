/*
 ============================================================================
 Name        : HW03.c
 Author      : Shimon desta 203670286 and Tal saar 209151380
 Copyright   : Your copyright notice
 Description : Airport Manager in C
 ============================================================================
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include "General.h"
#include "Date.h"

const int DAY_MONTHS[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

int	 checkDate(char* date)
{
	int day, month, year;
	if (strlen(date) != 10)
		return 0;

	sscanf(date, "%d/%d/%d", &day, &month, &year);
	if (day < 1 || month < 1 || month > 12 || year < MIN_YEAR)
		return 0;

	if (day > DAY_MONTHS[month - 1])
		return 0;


	return 1;
}
void printDate(const Date* date) 
{
	printf("Date: %2d/%2d/%2d\n", date->day, date->month, date->year);
	
}
void printTheDate(const char* date)
{
	printf("%s", date);
}
void initDate(Date* pDate, char* str) {
	sscanf(str, "%d/%d/%d", &pDate->day, &pDate->month, &pDate->year);
}
int compareDate(const Date* date1, const Date* date2)
{

	if (date1->day == date2->day && date1->month == date2->month && date1->year == date2->year)
		return 0;

	if (date1->year > date2->year)
		return 1;
	else
		return -1;

	if (date1->month > date2->month)
		return 1;
	else
		return -1;

	if (date1->day > date2->day)
		return 1;

	return -1;
}