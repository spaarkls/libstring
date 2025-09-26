#ifndef SSCANF_H
#define SSCANF_H
#include <ctype.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>

#include "s21_string.h"

#define isflags(F) (F == 'l' || F == 'h' || F == 'L')
#define isspecifier(S)                                                     \
  (S == 's' || S == 'd' || S == 'f' || S == 'c' || S == 'i' || S == 'e' || \
   S == 'E' || S == 'g' || S == 'o' || S == 'u' || S == 'x' || S == 'X' || \
   S == 'p' || S == 'n' || S == 'G')
#define isinteger_t(S)                                                     \
  (S == 'd' || S == 'o' || S == 'x' || S == 'i' || S == 'X' || S == 'u' || \
   S == 'n' || S == 'p')
#define isuint(S) (S == 'o' || S == 'x' || S == 'X' || S == 'u' || S == 'p')
#define isint(S) (S == 'd' || S == 'i' || S == 'n')
#define isfloat_t(S) (S == 'f' || S == 'e' || S == 'E' || S == 'g' || S == 'G')
#define OCT 8
#define DECIMAL 10
#define HEX 16
#define ischar_t(S) (S == 's' || S == 'c')
#define isoctal(D) (D >= '0' && D <= '7')
#define ident_oct(D) (D == '0')

#define ident_hex(D) (D == 'x' || D == 'X')
#define ishex_alpha(D) ((D >= 'a' && D <= 'f') || (D >= 'A' && D <= 'F'))
#define ishex(D) (isdigit(D) || ishex_alpha(D))
#define isexp_dec(E) (E == 'e' || E == 'E')
#define isexp_bin(E) (E == 'p' || E == 'P')
#define issign(S) (S == '-' || S == '+')

typedef struct {
  int specifier;
  int suppressing;
  long int result;
  long int width;
  long int length;
  int f_long_int;
  int f_long_float;
  int f_short;
} Flags;

typedef enum { INIT, ASSGN, SIGN } Operation_obj;

int s21_sscanf(const char *, const char *, ...);
const char *init_width(const char *, long int *);
const char *read_flags(const char *, Flags *);
const char *set_length_flag(const char *, Flags *);
void write_pointer(void **, void *);
Flags default_init_flags(Flags *);

typedef const char *(Write_type)(va_list *, const char *, Flags *);
Write_type write_data;
Write_type write_char_type;
Write_type write_integer_type;
Write_type write_float_type;

typedef void(Write_char_type)(const char *, void *, int);
typedef const char *(Write_char)(const char *, void *, Flags *, Write_char_type,
                                 s21_size_t);

Write_char_type write_char_t;
Write_char_type write_wchar_t;
Write_char write_chars;
Write_char write_char;

typedef void(Write_integer_type)(void *, void *, int, int, Operation_obj);
typedef const char *(Write_integer)(va_list *, const char *, Flags *);
typedef const char *(Number_system)(const char *, void *, Flags *,
                                    Write_integer_type *);

Number_system write_decimal;
Number_system write_octal;
Number_system write_hex;
Number_system write_multi_int;
Write_integer write_integer;
Write_integer write_uinteger;
Write_integer_type write_integer_t;
Write_integer_type write_hinteger_t;
Write_integer_type write_linteger_t;
Write_integer_type write_uinteger_t;
Write_integer_type write_uhinteger_t;
Write_integer_type write_ulinteger_t;

typedef void(Write_float_type)(void *, const char *);
const char *write_float(const char *pstr, void *pwrite, Flags *flags,
                        Write_float_type *write);
Write_float_type write_float_t;
Write_float_type write_double_t;
Write_float_type write_Ldouble_t;
#endif