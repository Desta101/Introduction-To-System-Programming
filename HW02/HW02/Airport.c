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
			res.name = add_two_spaces(res.name);
			res.name[0] = toupper(res.name[0]);//First letter to upepr
		}
		else
		{
			res.country = get_str_exact_len(i);
			fix_string(res.country);
			res.country = add_two_spaces(res.country);
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
int is_valid_code(char* code){
	if (strlen(code) <= 2 || strlen(code) >= 4)
		return 0;
	return 1;
}

void fix_string(char* str){
	chack_start_spaces(str);
	chack_end_spaces(str);
	fix_spaces(str);
	if (strlen(str) == 0){
		return NULL;
	}
	int works = counter_of_words(str);
	int letters_in_word = 0;
	if (works == 1) {
		return str;
	}
	while (works != 0) {
		if (*(str - 1) == ' ' || works != 1) {
			letters_in_word = counter_of_letter(str);
			chack_the_word_even_or_odd(str, letters_in_word); 
			str += letters_in_word; 
			works--; 
		}
		str++;
	}
	if (counter_word_last(str) % 2 == 0) {
		chack_the_word_even_or_odd(str, counter_word_last(str));
	}
	chack_last_word(str); 
}

void chack_start_spaces(char* str){
	if (*str == ' ')
	{
		while (*str == ' ') str++;
	}
}

void chack_end_spaces(char * str){
	int index = -1, i = 0;
	while (str[i] != '\0'){
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n'){
			index = i;
		}
		i++;
	}
	str[index + 1] = '\0';
}

void fix_spaces(char* str){   
	int no_space = 0, flag = 0;
	char* pLook = str;
	char* pWrite = str;
	char* pEnd = str;
	while (*pLook) {

		if (*pLook != ' ') {
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

char* add_two_spaces(char* str) {
	int i = 0, no_space = 0, len, j = 0, flag = 1;
	char* pLook = str;
	char* pCopy = str;
	char* pWrite = NULL;

	while (*pCopy) {
		if (*pCopy == ' ') {
			i++;
		}
		i++;
		pCopy++;
	}
	pWrite = (char*)malloc((i) * sizeof(char));
	i = 0;
	while (*pLook) {

		if (*pLook != ' ') {
			pWrite[i] = *pLook;
			no_space = 1;
			i++;
		}
		else if((*pLook == ' ') && (no_space)){
			pWrite[i] = ' ';
			i++;
			pWrite[i] = ' ';
			i++;
			no_space = 0;

		}
		pLook++;
	}
	pWrite[i] = '\0';
	return pWrite;
}
void chack_last_word(char* string) {
	string[0] = tolower(string[0]);

}
int counter_of_words(char* str){
	int flag = 0;
	int count = 0;
	while (*str != '\0')
	{
		if (*str == ' ')
		{
			flag = 1;
		}
		else if (flag == 1)
		{
			flag = 0;
			count++;
		}
		str++;
	}
	return count;
}

int counter_of_letter(char* word){
	int count = 0;
	while (*word != ' ' )
	{
		count++;
		word++;
	}
	return count;
}

int counter_word_last(char* word){
	int count = 0;
	while (*word != '\0')
	{
		count++;
		word++;
	}
	return count;
}
void chack_the_word_even_or_odd(char* word, int characters){
	if (characters % 2 == 0){
		for (int i = 0; i < characters; i++){
			if (i % 2 == 0){
				*word = toupper(*word);
			}
			else{
				*word = tolower(*word);
			}
			*word++;
		}
	}
	else{
		*word = toupper(*word);
	}

}



