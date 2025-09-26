#include "s21_sscanf.h"

int s21_sscanf(const char *str, const char *format, ...) {
  const char *pstr = str, *pfmt = format, *ppstr = pstr;
  Flags flags = default_init_flags(S21_NULL);
  int end = 0;
  va_list ap;
  va_start(ap, format);
  while (TRUE) {
    if (flags.specifier) {
      if (flags.specifier == 'c' || !isspace(*pstr)) {
        ppstr = write_data(&ap, pstr, &flags);
        if (ppstr > pstr || flags.specifier == 'n') {
          flags.length += ppstr - pstr;
          pstr = ppstr;
          if (!flags.suppressing && flags.specifier != 'n') ++flags.result;
          flags = default_init_flags(&flags);
          ++pfmt;
        } else {
          end = 1;
        }
      } else {
        ++pstr;
        ++flags.length;
      }
    } else if (*pfmt == '%') {
      pfmt = read_flags(++pfmt, &flags);
      if (isspecifier(*pfmt)) {
        flags.specifier = *pfmt;
      } else if (*pfmt == '%') {
        if (*pstr == '%') {
          ++pstr;
          ++pfmt;
          ++flags.length;
        } else
          end = 1;
      }
    } else if (isspace(*pfmt) && isspace(*pstr)) {
      ++pstr;
      ++flags.length;
    } else if (*pstr &&
               (*pfmt == *pstr || (isspace(*pfmt) && !isspace(*pstr)))) {
      if (*pfmt == *pstr) {
        ++pstr;
        ++flags.length;
      }
      ++pfmt;
    } else {
      end = 1;
    }
    if (!(*pfmt && *pstr) || end) break;
    end = 0;
  }
  va_end(ap);
  return flags.result;
}

const char *write_data(va_list *ap, const char *pstr, Flags *flags) {
  if (ischar_t(flags->specifier)) {
    pstr = write_char_type(ap, pstr, flags);

  } else if (isinteger_t(flags->specifier)) {
    pstr = write_integer_type(ap, pstr, flags);

  } else if (isfloat_t(flags->specifier)) {
    pstr = write_float_type(ap, pstr, flags);
  }
  return pstr;
}

const char *write_float_type(va_list *ap, const char *pstr, Flags *flags) {
  if (flags->f_long_int) {
    double *pdbl = S21_NULL;
    if (!flags->suppressing) pdbl = va_arg(*ap, double *);
    pstr = write_float(pstr, pdbl, flags, write_double_t);
  } else if (flags->f_long_float) {
    long double *pdbl = S21_NULL;
    if (!flags->suppressing) pdbl = va_arg(*ap, long double *);
    pstr = write_float(pstr, pdbl, flags, write_Ldouble_t);
  } else {
    float *pdbl = S21_NULL;
    if (!flags->suppressing) pdbl = va_arg(*ap, float *);
    pstr = write_float(pstr, pdbl, flags, write_float_t);
  }
  return pstr;
}

const char *write_integer_type(va_list *ap, const char *pstr, Flags *flags) {
  if (isint(flags->specifier)) {
    pstr = write_integer(ap, pstr, flags);

  } else if (isuint(flags->specifier)) {
    pstr = write_uinteger(ap, pstr, flags);
  }
  return pstr;
}
const char *write_float(const char *pstr, void *pwrite, Flags *flags,
                        Write_float_type *write) {
  char buff[1024];
  for (int i = 0; i < 1024; ++i) buff[i] = '\0';
  char *pb = buff;
  const char *pivot = pstr;
  long int width = flags->width;
  int vld = 0, hex = 0;
  if (*pivot == '+' || *pivot == '-') {
    *pb++ = *pivot++;
    --width;
  }
  if (!(isdigit(*pivot) || *pivot == '.') || !width) return pstr;
  if (*pivot == '0') {
    *pb++ = *pivot++;
    --width;
    if (ident_hex(*pivot) && width) {
      hex = 1;
      *pb++ = *pivot++;
      --width;
    } else
      vld = 1;
    if (!width) {
      vld = 1;
      if (hex) --pivot;
    }
  }
  for (; ((isdigit(*pivot) || (ishex_alpha(*pivot) && hex)) && width);
       ++pivot, ++pb, --width) {
    vld = 1;
    *pb = *pivot;
  }
  if (*pivot == '.' && width) {
    if (hex) vld = 1;
    *pb++ = *pivot++;
    --width;
    if ((isdigit(*pivot) || (ishex_alpha(*pivot) && hex)) && width) {
      vld = 1;
      for (; ((isdigit(*pivot) || (ishex_alpha(*pivot) && hex)) && width);
           ++pivot, ++pb, --width)
        *pb = *pivot;
    }
  }
  if (vld) {
    if (((isexp_dec(*pivot) ||
          ((isexp_bin(*pivot)) && hex && pb - buff > 3))) &&
        width) {
      *pb++ = *pivot++;
      --width;
      if (issign(*pivot) && width) {
        *pb++ = *pivot++;
        --width;
      }
      for (; !(!isdigit(*pivot) || width == 0); ++pivot, ++pb, --width)
        *pb = *pivot;
    }
    pstr = pivot;
    *pb = '\0';
    if (!flags->suppressing) write(pwrite, buff);
  }
  return pstr;
}
const char *write_uinteger(va_list *ap, const char *pstr, Flags *flags) {
  if (flags->specifier == 'X') flags->specifier = 'x';
  if (flags->specifier == 'p') {
    void **pvoid = S21_NULL;
    if (!flags->suppressing) pvoid = va_arg(*ap, void **);
    unsigned int pint = 0;
    pstr = write_hex(pstr, &pint, flags, write_uinteger_t);
    if (!flags->suppressing) write_pointer(pvoid, &pint);
  } else if (flags->f_short) {
    unsigned short int *phint = S21_NULL;
    if (!flags->suppressing) phint = va_arg(*ap, unsigned short int *);
    switch (flags->specifier) {
      case 'u':
        pstr = write_decimal(pstr, phint, flags, write_uhinteger_t);
        break;
      case 'o':
        pstr = write_octal(pstr, phint, flags, write_uhinteger_t);
        break;
      case 'x':
        pstr = write_hex(pstr, phint, flags, write_uhinteger_t);
        break;
    }
  } else if (flags->f_long_int) {
    unsigned long int *plint = S21_NULL;
    if (!flags->suppressing) plint = va_arg(*ap, unsigned long int *);
    switch (flags->specifier) {
      case 'u':
        pstr = write_decimal(pstr, plint, flags, write_ulinteger_t);
        break;
      case 'o':
        pstr = write_octal(pstr, plint, flags, write_ulinteger_t);
        break;
      case 'x':
        pstr = write_hex(pstr, plint, flags, write_ulinteger_t);
        break;
    }
  } else {
    unsigned int *pint = S21_NULL;
    if (!flags->suppressing) pint = va_arg(*ap, unsigned int *);
    switch (flags->specifier) {
      case 'u':
        pstr = write_decimal(pstr, pint, flags, write_uinteger_t);
        break;
      case 'o':
        pstr = write_octal(pstr, pint, flags, write_uinteger_t);
        break;
      case 'x':
        pstr = write_hex(pstr, pint, flags, write_uinteger_t);
        break;
    }
  }
  return pstr;
}

const char *write_integer(va_list *ap, const char *pstr, Flags *flags) {
  if (flags->f_short) {
    short int *phint = S21_NULL;
    if (!flags->suppressing) phint = va_arg(*ap, short int *);
    switch (flags->specifier) {
      case 'd':
        pstr = write_decimal(pstr, phint, flags, write_hinteger_t);
        break;
      case 'i':
        pstr = write_multi_int(pstr, phint, flags, write_hinteger_t);
        break;
      case 'n':
        if (!flags->suppressing) *phint = flags->length;
        break;
    }
  } else if (flags->f_long_int) {
    long int *plint = S21_NULL;
    if (!flags->suppressing) plint = va_arg(*ap, long int *);
    switch (flags->specifier) {
      case 'd':
        pstr = write_decimal(pstr, plint, flags, write_linteger_t);
        break;
      case 'i':
        pstr = write_multi_int(pstr, plint, flags, write_linteger_t);
        break;
      case 'n':
        if (!flags->suppressing) *plint = flags->length;
        break;
    }
  } else {
    int *pint = S21_NULL;
    if (!flags->suppressing) pint = va_arg(*ap, int *);
    switch (flags->specifier) {
      case 'd':
        pstr = write_decimal(pstr, pint, flags, write_integer_t);
        break;
      case 'i':
        pstr = write_multi_int(pstr, pint, flags, write_integer_t);
        break;
      case 'n':
        if (!flags->suppressing) *pint = flags->length;
        break;
    }
  }
  return pstr;
}

const char *write_multi_int(const char *pstr, void *pwrite, Flags *flags,
                            Write_integer_type *write) {
  int sign = 0;
  if (issign(*pstr)) {
    ++pstr;
    sign = 1;
    if (!isdigit(*pstr)) return --pstr;
  }
  if (ident_oct(*pstr)) {
    ++pstr;
    if (ident_hex(*pstr)) {
      pstr = write_hex(pstr - (1 + sign), pwrite, flags, write);
    } else {
      pstr = write_octal(pstr - (1 + sign), pwrite, flags, write);
    }
  } else if (isdigit(*pstr)) {
    pstr = write_decimal(pstr - sign, pwrite, flags, write);
  }
  return pstr;
}
const char *write_hex(const char *pstr, void *pwrite, Flags *flags,
                      Write_integer_type *write) {
  long int res = 0, width = flags->width, sign = 1;
  if (issign(*pstr)) {
    if (*pstr == '-') sign = -sign;
    ++pstr;
    --width;
    if (!ishex(*pstr) || width == 0) return --pstr;
  }
  if (ishex(*pstr) && !flags->suppressing) write(pwrite, &res, sign, HEX, INIT);
  if (*pstr == '0') {
    ++pstr;
    --width;
    if (ident_hex(*pstr) && width) {
      ++pstr;
      --width;
    }
  }
  for (; ishex(*pstr) && width; ++pstr, --width) {
    if (isdigit(*pstr)) {
      res = *pstr - '0';
    } else {
      res = toupper(*pstr) - 55;
    }
    if (!flags->suppressing) write(pwrite, &res, sign, HEX, ASSGN);
  }
  if (!flags->suppressing) write(pwrite, &res, sign, HEX, SIGN);
  return pstr;
}

const char *write_octal(const char *pstr, void *pwrite, Flags *flags,
                        Write_integer_type *write) {
  long int res = 0, sign = 1, width = flags->width;
  if (issign(*pstr)) {
    if (*pstr == '-') sign = -sign;
    ++pstr;
    --width;
    if (!isoctal(*pstr) || width == 0) return --pstr;
  }
  if (isoctal(*pstr) && !flags->suppressing)
    write(pwrite, &res, sign, OCT, INIT);

  for (; !(!isoctal(*pstr) || width == 0); ++pstr, --width) {
    res = *pstr - '0';
    if (!flags->suppressing) write(pwrite, &res, sign, OCT, ASSGN);
  }
  if (!flags->suppressing) write(pwrite, &res, sign, OCT, SIGN);

  return pstr;
}
const char *write_decimal(const char *pstr, void *pwrite, Flags *flags,
                          Write_integer_type *write) {
  long int res = 0, sign = 1, width = flags->width;
  if (issign(*pstr)) {
    if (*pstr == '-') sign = -sign;
    ++pstr;
    --width;
    if (!isdigit(*pstr) || !width) return --pstr;
  }
  if (isdigit(*pstr) && !flags->suppressing)
    write(pwrite, &res, sign, DECIMAL, INIT);
  for (; isdigit(*pstr) && width; ++pstr, --width) {
    res = *pstr - '0';
    if (!flags->suppressing) write(pwrite, &res, sign, DECIMAL, ASSGN);
  }
  if (!flags->suppressing) write(pwrite, &res, sign, DECIMAL, SIGN);

  return pstr;
}

const char *write_char(const char *pstr, void *pwrite, Flags *flags,
                       Write_char_type *write, s21_size_t step) {
  int width = flags->width;
  if (width < 0) width = 1;
  for (; width && *pstr; --width, ++pstr) {
    if (!flags->suppressing) {
      write(pstr, pwrite, 0);
      pwrite += step;
    }
  }
  return pstr;
}
void write_char_t(const char *source, void *dest, int end) {
  if (!end)
    *(char *)dest = *source;
  else
    *(char *)dest = '\0';
}
const char *write_char_type(va_list *ap, const char *pstr, Flags *flags) {
  char *pwrite = S21_NULL;
  if (!flags->suppressing) {
    if (flags->f_long_int || flags->f_long_float) {
      wchar_t *wpwrite = va_arg(*ap, wchar_t *);
      if (flags->specifier == 's')
        pstr =
            write_chars(pstr, wpwrite, flags, write_wchar_t, sizeof(wchar_t));
      else
        pstr = write_char(pstr, wpwrite, flags, write_wchar_t, sizeof(wchar_t));
    } else {
      pwrite = va_arg(*ap, char *);
      if (flags->specifier == 's')
        pstr = write_chars(pstr, pwrite, flags, write_char_t, sizeof(char));
      else
        pstr = write_char(pstr, pwrite, flags, write_char_t, sizeof(char));
    }
  } else {
    if (flags->specifier == 's')
      pstr = write_chars(pstr, pwrite, flags, write_char_t, sizeof(char));
    else
      pstr = write_char(pstr, pwrite, flags, write_char_t, sizeof(char));
  }
  return pstr;
}

const char *write_chars(const char *pstr, void *pwrite, Flags *flags,
                        Write_char_type *write, s21_size_t step) {
  int width = flags->width;
  for (; !isspace(*pstr) && *pstr && width; ++pstr, --width) {
    if (!flags->suppressing) {
      write(pstr, pwrite, 0);
      pwrite += step;
    }
  }
  if (!flags->suppressing) write(pstr, pwrite, 1);
  return pstr;
}

void write_wchar_t(const char *source, void *dest, int end) {
  if (!end)
    *(wchar_t *)dest = *source;
  else
    *(wchar_t *)dest = '\0';
}
const char *init_width(const char *pfmt, long int *width) {
  if (isdigit(*pfmt)) *width = 0;
  for (; isdigit(*pfmt); ++pfmt) *width = *width * 10 + *pfmt - '0';
  return pfmt;
}

const char *read_flags(const char *pfmt, Flags *flags) {
  if (isdigit(*pfmt)) {
    pfmt = init_width(pfmt, &(flags->width));
  } else if (*pfmt == '*') {
    flags->suppressing = 1;
    ++pfmt;
  }
  pfmt = set_length_flag(pfmt, flags);
  return pfmt;
}

const char *set_length_flag(const char *pfmt, Flags *flags) {
  if (isflags(*pfmt)) {
    switch (*pfmt) {
      case 'l':
        flags->f_long_int++;
        break;
      case 'L':
        flags->f_long_float++;
        break;
      case 'h':
        flags->f_short++;
        break;
    }
    ++pfmt;
  }
  return pfmt;
}

Flags default_init_flags(Flags *previous_flags) {
  Flags flags;
  flags.specifier = 0;
  flags.result = (previous_flags) ? previous_flags->result : 0;
  flags.width = -1;
  flags.suppressing = 0;
  flags.length = (previous_flags) ? previous_flags->length : 0;
  flags.f_long_int = 0;
  flags.f_long_float = 0;
  flags.f_short = 0;
  return flags;
}
void write_integer_t(void *obj, void *val, int sign, int notation,
                     Operation_obj operation) {
  switch (operation) {
    case INIT:
      *(int *)obj = 0;
      break;
    case ASSGN:
      *(int *)obj = *(int *)obj * notation + *(int *)val;
      break;
    case SIGN:
      *(int *)obj *= sign;
      break;
  }
}
void write_hinteger_t(void *obj, void *val, int sign, int notation,
                      Operation_obj operation) {
  switch (operation) {
    case INIT:
      *(short int *)obj = 0;
      break;
    case ASSGN:
      *(short int *)obj = *(short int *)obj * notation + *(short int *)val;
      break;
    case SIGN:
      *(short int *)obj *= sign;
      break;
  }
}

void write_linteger_t(void *obj, void *val, int sign, int notation,
                      Operation_obj operation) {
  switch (operation) {
    case INIT:
      *(long int *)obj = 0;
      break;
    case ASSGN:
      *(long int *)obj = *(long int *)obj * notation + *(long int *)val;
      break;
    case SIGN:
      *(long int *)obj *= sign;
      break;
  }
}

void write_uhinteger_t(void *obj, void *val, int sign, int notation,
                       Operation_obj operation) {
  switch (operation) {
    case INIT:
      *(unsigned short int *)obj = 0;
      break;
    case ASSGN:
      *(unsigned short int *)obj =
          *(unsigned short int *)obj * notation + *(unsigned short int *)val;
      break;
    case SIGN:
      *(unsigned short int *)obj *= sign;
      break;
  }
}

void write_ulinteger_t(void *obj, void *val, int sign, int notation,
                       Operation_obj operation) {
  switch (operation) {
    case INIT:
      *(unsigned long int *)obj = 0;
      break;
    case ASSGN:
      *(unsigned long int *)obj =
          *(unsigned long int *)obj * notation + *(unsigned long int *)val;
      break;
    case SIGN:
      *(unsigned long int *)obj *= sign;
      break;
  }
}

void write_uinteger_t(void *obj, void *val, int sign, int notation,
                      Operation_obj operation) {
  switch (operation) {
    case INIT:
      *(unsigned int *)obj = 0;
      break;
    case ASSGN:
      *(unsigned int *)obj =
          *(unsigned int *)obj * notation + *(unsigned int *)val;
      break;
    case SIGN:
      *(unsigned int *)obj *= sign;
      break;
  }
}
void write_float_t(void *obj, const char *str) { *(float *)obj = atof(str); }
void write_double_t(void *obj, const char *str) { *(double *)obj = atof(str); }
void write_Ldouble_t(void *obj, const char *str) {
  *(long double *)obj = atof(str);
}

void write_pointer(void **p, void *var) {
  *(unsigned int *)p = *(unsigned int *)var;
}
