#ifndef S21_SPRINTF_H
#define S21_SPRINTF_H
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"

#define MAX_NUM_LEN 350
#define SPECIFICATORS "csduxXopfeEgG%"
#define INT_SPECIFICATORS "duxXop"
#define UNSIGNED_SPECIFICATORS "uxXo"
#define FLOAT_SPECIFICATORS "feEgG"
#define FLAGS "-+ 0#"

typedef struct Flags {
  char minus;
  char plus;
  char space;
  char zero;
  char hash;
} Flags;

typedef struct Format {
  Flags fl;
  char is_negative;
  int width;
  int precision;
  char length;
  char type;
} Format;

// for sprint to str
int sprint_arg(char *dest, Format *fspec, va_list *args, int *error);
int sprint_str(char *dest, const char *str, const Format *fspec);
int sprint_wchar_str(char *dest, const wchar_t *str, const Format *fspec);
int sprint_buffer(char *dest, char *buffer, const Format *fspec);
int sprint_prefix(char *dest, s21_size_t str_len, const Format *fspec);

// utility functions
int zero_prefix_len(s21_size_t s_len, const Format *fspec);
int prefix_symbol_len(const Format *fspec);
int sprint_symbols(char *dest, int width, char ch);
int str_to_int(char **frm_str);
char s21_is_digit(char ch);

// for float numbers (%fgGeE)
void float_to_str(char *buffer, long double num, Format *fspec);
int offset_calc(int exp, int precision, char type);
void f_to_str(char *buffer, long double num, int *exp);
void round_str(char *buffer, int offset, int *exp);
void right_shift(char *buffer);
void cut_zero_for_g(char *buffer, int end, int flag_e);
void str_format_g(char *buffer, int exp, int offset, Format *fspec);
void str_format_f(char *buffer, int exp, const Format *fspec);
void str_format_e(char *buffer, int exp, Format *fspec);

// for int numbers (%duxXop)
void uint_to_str(char *buffer, long unsigned int num, char type);
void int_to_str(char *buffer, long long int num, Format *fspec);
void reverse_str(char *str);

// read format functions
void read_format(char **frm_str, Format *fspec, va_list *args, int *error);
void check_format_structure(Format *fspec, int *error);
void read_flag(Flags *fl, char ch);

#endif
