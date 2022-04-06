#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdarg.h>


#define CODE_LEN 3
#define MAX_LEN 255
#define DATE 11
typedef struct {
	char* name;
	char* country;
	char IATA[CODE_LEN + 1];//TO CHANGE BACK TO "CODE_LEN"

}Airport;

void general_array_function(void* arr, int size, int type_size, void (*print)(void*));

int is_identical_airport(Airport* one, Airport* two);
int is_identical_code(Airport* air, char* code);

int is_all_capitals(char* str);
int is_valid_code(char* code);


int get_airport_from_user(Airport* air, int pos);
char* get_str_exact_len(int opt);
int get_code(char* code, Airport* air, int pos);
char* my_gets(char* buf, size_t size);
void fix_string(char* name);
void chack_start_spaces(char* str);
void chack_end_spaces(char* str);
char* add_two_spaces(char* str);
int counter_of_words(char* str);
int counter_of_letter( char* word);
void chack_the_word_even_or_odd(char* word, int characters);
void chack_last_word(char* string);
int counter_word_last(char* word);
void fix_spaces(char* str);