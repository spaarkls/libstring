#ifndef TEST_S21_STRING_H
#define TEST_S21_STRING_H

#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"

#define SAMPLE_STRING "This is a sample string"
#define BIGGER_STRING "This is a bigger sample string"
#define UPPER_SAMPLE "THIS IS A SAMPLE STRING"
#define LOWER_SAMPLE "this is a sample string"
#define TWICE_SAMPLE "This is a sample stringThis is a sample string"
#define SPECIAL_CHARS_STRING \
  "!@#$%^&*()_+ This is a sample string with special characters"
#define SPECIAL_CHARS_UPPER \
  "!@#$%^&*()_+ THIS IS A SAMPLE STRING WITH SPECIAL CHARACTERS"
#define SPECIAL_CHARS_LOWER \
  "!@#$%^&*()_+ this is a sample string with special characters"
#define NON_PRINTABLE_STRING \
  "This\n is\t a sample string with non-printable characters"
#define EXTENDED_ASCII_STRING "«Thís ïs á sàµplé sτríñg»"
#define STRING_WITH_NULL "This is a sample \0 string"
#define STRING_WITH_MULTIPLE_NULLS "This is a \0 sample \0 string"
#define STRING_W_CONSEC_COMA_DELIMS "This,,is a sample string"
#define STRING_W_LEADING_COMA_DELIM ",This,is a sample string"
#define STRING_W_TRAILING_COMA_DELIM "This is a sample,string,"
#define ONLY_COMAS_STRING ",,,,"
#define STRING_W_MIXED_DELIMS "This is,a.sample/string"
#define NONE_IN_SAMPLE "XyzZ!"
#define ONE_IN_SAMPLE "Zebra"
#define WORD_IN_SAMPLE "sample"
#define WORD_IN_SAMPLE_TWICE "samplesample"
#define WORD_IN_SAMPLE_NON_PRINTABLE "\tsample\n"
#define WORD_IN_SAMPLE_SPECIAL_CHARS "sample!@#$%^&*()_+"
#define EXTENDED_ASCII_WORD "sàµplé"
#define FIRST_WORD "This"
#define LAST_WORD "string"
#define WORD_TWICE_IN_SAMPLE "is"
#define CHAR_TO_FIND 's'
#define CHAR_NOT_FOUND 'z'
#define CHAR_NON_PRINTABLE '\n'
#define EXTENDED_ASCII_CHAR '\xb5'
#define EMPTY_STRING ""
#define DELIM " "
#define NOT_A_DELIM "!"
#define COMA_DELIM ","
#define MIXED_DELIMS " ,./"
#define STR_LEN 64
#define DEC -1
#define D_FLOAT -1.1
#define U_DEC 1
#define PI 3.14159265359
#define VERY_SMALL_VAL 0.0000000001
#define LONG_INT 8888888888
#define LARGE_SIZE 1000000

void run_strtok_tests(char *str, char *delim);

#endif