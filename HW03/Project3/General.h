#ifndef __GENERAL__
#define __GENERAL__
#include "Date.h"
#define MAX_STR_LEN 255
#define MIN_YEAR 2020



char*	getStrExactName(const char* msg);
char*  getStrExactstrfromFile(FILE* f);
double	getDoubleCheckLimits(const char* msg, double start, double end);
char*	myGets(char* buffer, int size,FILE* f);
char*  getDynStr(char* str);
char*	getCorrectDate();

char* myGetsdate(char* buffer, int size);
void generalArrayFunction(void* arr, int length, int size, void (*f)(void*));
char* getStrExactLength(FILE* source);
char**	splitCharsToWords(char* str, int* pCount, int* pTotalLength);

#endif

