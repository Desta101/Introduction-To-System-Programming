#include "Airport.h"

//Generic printing and releasing data
void general_array_function(void* arr, int size, int type_size, void (*action)(void*))
{
	action(arr);
}
//checking for identical codes
int is_identical_airport(Airport* one, Airport* two)
{
	if (strcmp(one->IATA, two->IATA) == 0)
		return 1;
	return 0;
}
// checking if code is compatible
int is_identical_code(Airport* air, char* code)
{
	if (strcmp(air->IATA, code) == 0)
		return 1;
	return 0;
}

//getting airport from user
int get_airport_from_user(Airport* air, int pos)
{
	int i;
	Airport res;
	get_code(res.IATA, air, pos);
	for (i = 0; i < 2; i++)
	{
		if (i == 0)
		{
			res.name = get_str_exact_len(i);
			fix_string(res.name);
			res.name=fix_word(res.name);
			res.name[0] = toupper(res.name[0]);//First letter to upepr
		}
		else
		{
			res.country = get_str_exact_len(i);
			fix_string(res.country);
			res.country = fix_word(res.country);
			res.country[0] = toupper(res.country[0]);//First letter to upepr
		}
	}
	air[pos] = res;
	return 1;
}
//getting exact length of string
char* get_str_exact_len(int opt)
{
	char* the_str = NULL;
	int len;
	char input_str[MAX_LEN];
	char str[MAX_LEN];
	//Ask for a string from the user
	if (opt == 0)
		printf("Enter airport name:");
	else if (opt == 1)
		printf("Enter airport country:");
	else if (opt == 2)
		printf("Enter airline name:");
	else if (opt == 3)
		printf("Enter Origine to check from: ");
	else
		printf("Enter Destination to check to: ");
	my_gets(input_str, sizeof(input_str));
	//find string size and add 1 for the '\0'
	len = strlen(input_str) + 1;
	//allocate a place for the string in the right location in the array 
	the_str = (char*)malloc(len * sizeof(char));
	//Copy the string to the right location in the array 
	if (the_str != NULL)
		strcpy(the_str, input_str);
	if (opt == 3 )
		if (!is_valid_code(input_str) || !is_all_capitals(input_str))
			return NULL;

	return the_str;
}
//getting fixed string
char* my_gets(char* buf, size_t size)
{
	fflush(stdin);
	if (buf != NULL && size > 0)
	{		
		if (fgets(buf, size, stdin))
		{
			buf[strcspn(buf, "\n")] = '\0';
			return buf;
		}
		*buf = '\0';
	}
	return NULL;
}
//getting iata code
int get_code(char* code, Airport* air, int pos)
{
	int bool = 0, i;
	int res;
	char input_buf[MAX_LEN] = { '\0' };
	res = getchar();
	while (!bool)
	{
		int flag_ident = 0;
		printf("Enter 3 letter IATA code: ");
		if (!fgets(input_buf, MAX_LEN - 1, stdin))
			return 0;
		input_buf[strcspn(input_buf, "\n")] = 0;
		for (i = 0; i < pos; i++)
		{
			if (is_identical_code(&air[i], input_buf) == 1)
			{
				printf("Code already exist! Try Again...\n");
				flag_ident = 1;
			}
		}
		if (!flag_ident && !bool)
		{
			if (is_valid_code(input_buf) == 0 || is_all_capitals(input_buf) == 0)
				printf("Wrong input! Try Again...\n");
			else
				bool = 1;
		}
	}
	strcpy(code, input_buf);
	return 1;
}
//checking if all letters in iata are capitals
int is_all_capitals(char* str)
{
	// counting for upper case
	char ch;
	int i = 0;
	ch = str[i];
	while (i < CODE_LEN)
	{
		ch = str[i++];
		if (!isupper(ch))
			return 0;
	}
	return 1;
}
//checking if iata code is in right length
int is_valid_code(char* code)
{
	if (strlen(code) <= 2 || strlen(code) >= 4)
		return 0;
	return 1;
}

void fix_string(char* str) {
	int no_space = 0, flag = 0;
	char* pLook = str;
	char* pWrite = str;
	char* pEnd = str;
	while (*pLook == ' ')
		pLook++;
	while (*pLook) {

		if (*pLook != ' ') {
			if (*pLook >= 'A'&& *pLook <= 'Z') {
				if ((*pLook - 1) == ' ')
					*pWrite = *pLook;
				else
					*pWrite = *pLook + 0x20;
			}
			else
				*pWrite = *pLook;
			pWrite++;
			no_space = 1;

		}
		else if ((*pLook == ' ') && (no_space)) {
			*pWrite = *pLook;
			pWrite++;


			no_space = 0;
		}


		pLook++;
	}
	*pWrite = '\0';
}

char* fix_word(char* str) {
	int i = 0, len,j=0, flag=1;
	char* pLook = str;
	char* pCopy = str;
	char* pWrite = NULL;
	while (*pLook) {
		if (*pLook == ' ') {
			i++;
			j++;
		}
		i++;
		pLook++;
	}
	pWrite = (char*)malloc((i+1)* sizeof(char));
	i = 0;
	while (*pCopy) {

		if (*pCopy != ' ') {
			if (*(pCopy-1) == ' '&&j!=flag) {
				pWrite[i] = toupper(*pCopy);
				flag++;
			}
			else
				pWrite[i] = *pCopy;
			i++;
		}
		else {
			pWrite[i] = ' ';
			i++;
			pWrite[i] = ' ';
			i++;

		}
		pCopy++;
	}
	pWrite[i] = '\0';
	return pWrite;
}