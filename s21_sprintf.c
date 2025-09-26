#include "s21_sprintf.h"

int s21_sprintf(char *str, const char *format, ...) {
  int error = 0;
  va_list args;
  va_start(args, format);
  char *format_ptr = (char *)format;
  char *str_ptr = str;
  for (; (format_ptr) && *format_ptr != '\0' && !error;) {
    if (*format_ptr != '%') {
      *(str_ptr++) = *(format_ptr++);
    } else {
      if (*(format_ptr + 1) != '\0') {
        Format fspec = {.precision = -1};
        read_format(&format_ptr, &fspec, &args, &error);
        if (!error) str_ptr += sprint_arg(str_ptr, &fspec, &args, &error);
      } else {
        fprintf(stderr, "ERROR: after %% must be specificator\n");
        error = 1;
      }
    }
  }
  *str_ptr = '\0';
  va_end(args);
  return str_ptr - str;
}

void read_format(char **frm_str, Format *fspec, va_list *args, int *error) {
  char end_flags = 0;
  char *ptr = *frm_str + 1;
  while (ptr && *ptr != '\0' && !(end_flags && *ptr == ' ') && !(fspec->type) &&
         !(*error)) {
    if (!end_flags && s21_strchr(FLAGS, (*ptr))) {
      read_flag(&(fspec->fl), *ptr);
      ptr++;
    } else {
      end_flags = 1;
      if (s21_is_digit(*ptr) || *ptr == '*') {
        if (fspec->width == 0) {
          fspec->width = (*ptr == '*') ? va_arg(*args, int) : str_to_int(&ptr);
          ptr++;
        } else {
          fprintf(stderr, "ERROR: double width in one specificator\n");
          *error = 1;
        }
      } else if (*ptr == '.') {
        if (fspec->precision == -1) {
          ptr++;
          fspec->precision =
              (*ptr == '*') ? va_arg(*args, int) : str_to_int(&ptr);
          ptr++;
        } else {
          fprintf(stderr, "ERROR: double precision in one specificator\n");
          *error = 1;
        }
      } else if (*ptr == 'h' || *ptr == 'l' || *ptr == 'L') {
        fspec->length = *(ptr++);
      } else {
        fspec->type = *(ptr++);
      }
    }
  }
  if (!*error) check_format_structure(fspec, error);
  *frm_str = ptr;
}

void read_flag(Flags *fl, char ch) {
  if (ch == '-') {
    fl->minus = 1;
  } else if (ch == '+') {
    fl->plus = 1;
  } else if (ch == ' ') {
    fl->space = 1;
  } else if (ch == '#') {
    fl->hash = 1;
  } else if (ch == '0') {
    fl->zero = 1;
  }
}

char s21_is_digit(char ch) {
  char res = 0;
  if (ch >= 48 && ch <= 57) res = 1;
  return res;
}

int str_to_int(char **frm_str) {
  int res = 0;
  char buffer[11] = {0};
  char *ptr = *frm_str;
  int i = 0;
  for (; i < 10 && s21_is_digit(*ptr); i++) {
    buffer[i] = *ptr++;
  }
  buffer[i--] = '\0';
  *frm_str = ptr - 1;
  for (int m = 1; i >= 0; i--, m *= 10) {
    res += (buffer[i] - '0') * m;
  }
  return res;
}

void check_format_structure(Format *fspec, int *error) {
  if (!s21_strchr(SPECIFICATORS, fspec->type)) {
    fprintf(stderr, "ERROR: unknown specificator %c\n", fspec->type);
    *error = 1;
    return;
  }
  if (s21_strchr("sc", fspec->type)) {
    fspec->fl.zero = 0;
    fspec->fl.plus = 0;
    fspec->fl.hash = 0;
    fspec->fl.space = 0;
  }
  if (s21_strchr(FLOAT_SPECIFICATORS, fspec->type)) {
    if (fspec->fl.minus) fspec->fl.zero = 0;
    if (fspec->precision == -1) fspec->precision = 6;
  }
  if (fspec->type == 'd' || fspec->type == 'u') fspec->fl.hash = 0;
  if (s21_strchr("xXo", fspec->type)) {
    fspec->fl.plus = 0;
    fspec->fl.space = 0;
  }
  if (fspec->type == 'p') fspec->fl.hash = 1;
}

int sprint_arg(char *dest, Format *fspec, va_list *args, int *error) {
  char *ptr = dest;
  char *buffer =
      calloc(MAX_NUM_LEN + (fspec->precision) + (fspec->width), sizeof(char));
  if (buffer != S21_NULL) {
    if (fspec->type == 'd') {
      long long int num = va_arg(*args, long long int);
      if (fspec->length == 'h')
        num = (short int)num;
      else if (fspec->length != 'l')
        num = (int)num;
      int_to_str(buffer, num, fspec);
    } else if (s21_strchr(UNSIGNED_SPECIFICATORS, fspec->type)) {
      long unsigned int num = va_arg(*args, long unsigned int);
      if (fspec->length == 'h')
        num = (short unsigned int)num;
      else if (fspec->length != 'l')
        num = (unsigned int)num;
      uint_to_str(buffer, num, fspec->type);
    } else if (s21_strchr(FLOAT_SPECIFICATORS, fspec->type)) {
      if (fspec->length == 'L') {
        long double num = va_arg(*args, long double);
        float_to_str(buffer, num, fspec);
      } else {
        double num = va_arg(*args, double);
        float_to_str(buffer, num, fspec);
      }
    } else if (fspec->type == 'p') {
      void *num = va_arg(*args, void *);
      uint_to_str(buffer, (long unsigned int)num, fspec->type);
    } else if (fspec->type == '%') {
      *(ptr++) = '%';
    } else if (fspec->type == 'c') {
      if (fspec->length == 'l' || fspec->length == 'L') {
        wchar_t ch = va_arg(*args, wchar_t);
        buffer[0] = ch;
      } else {
        char ch = va_arg(*args, int);
        buffer[0] = ch;
      }
    } else if (fspec->type == 's') {
      if (fspec->length == 'l' || fspec->length == 'L') {
        const wchar_t *s = va_arg(*args, wchar_t *);
        ptr += sprint_wchar_str(ptr, s, fspec);
      } else {
        const char *s = va_arg(*args, char *);
        ptr += sprint_str(ptr, s, fspec);
      }
    }
    if (fspec->type != 's') ptr += sprint_buffer(ptr, buffer, fspec);
    free(buffer);
  } else {
    fprintf(stderr, "ERROR: memory allocation failed.\n");
    *error = 1;
  }
  return ptr - dest;
}

int sprint_buffer(char *dest, char *buffer, const Format *fspec) {
  char *ptr = dest;
  s21_size_t str_len = s21_strlen(buffer);
  ptr += sprint_prefix(ptr, str_len, fspec);
  for (int i = 0; buffer[i]; i++) *(ptr++) = buffer[i];
  if (fspec->fl.minus) {
    int suffix_width = fspec->width - (ptr - dest);
    ptr += sprint_symbols(ptr, suffix_width, ' ');
  }
  return ptr - dest;
}

int sprint_str(char *dest, const char *str, const Format *fspec) {
  char *ptr = dest;
  int len = (fspec->precision >= 0) ? fspec->precision : (int)s21_strlen(str);
  int width = (fspec->width) - len;
  if (!fspec->fl.minus) ptr += sprint_symbols(ptr, width, ' ');
  for (int i = 0; i < len && str[i]; i++) *(ptr++) = str[i];
  if (fspec->fl.minus) ptr += sprint_symbols(ptr, width, ' ');
  return ptr - dest;
}

int sprint_wchar_str(char *dest, const wchar_t *str, const Format *fspec) {
  char *ptr = dest;
  int w_len = 0;
  for (int i = 0; str[i]; i++) w_len++;
  w_len = (fspec->precision > 0) ? fspec->precision : w_len;
  int width = (fspec->width) - w_len;
  if (!fspec->fl.minus) ptr += sprint_symbols(ptr, width, ' ');
  for (int i = 0; str[i]; i++) *(ptr++) = str[i];
  if (fspec->fl.minus) ptr += sprint_symbols(ptr, width, ' ');
  return ptr - dest;
}

int sprint_symbols(char *dest, int width, char ch) {
  char *ptr = dest;
  for (int j = 0; j < width; j++) *(ptr++) = ch;
  return ptr - dest;
}

int sprint_prefix(char *dest, s21_size_t str_len, const Format *fspec) {
  char *ptr = dest;
  int zero_prefix = zero_prefix_len(str_len, fspec);
  int width = fspec->width - str_len - prefix_symbol_len(fspec) - zero_prefix;
  if (width > 0 && !fspec->fl.minus) {
    ptr += sprint_symbols(ptr, width, ' ');
  }
  if (fspec->is_negative)
    *ptr++ = '-';
  else if (fspec->fl.plus && !s21_strchr("o", fspec->type))
    *ptr++ = '+';
  else if (fspec->fl.space && !s21_strchr("o", fspec->type))
    *ptr++ = ' ';
  if (fspec->fl.hash) {
    if (s21_strchr("xXop", fspec->type)) {
      *ptr++ = '0';
      if (fspec->type != 'o') *ptr++ = (fspec->type == 'X') ? 'X' : 'x';
    }
  }
  if (zero_prefix > 0) ptr += sprint_symbols(ptr, zero_prefix, '0');
  return ptr - dest;
}

int prefix_symbol_len(const Format *fspec) {
  char res = 0;
  if (fspec->is_negative || fspec->fl.plus || fspec->fl.space) res += 1;
  if (fspec->fl.hash) {
    if (fspec->type == 'o')
      res += 1;
    else if (s21_strchr("xXp", fspec->type))
      res += 2;
  }
  return res;
}

int zero_prefix_len(s21_size_t s_len, const Format *fspec) {
  int zero = 0;
  if (s21_strchr(INT_SPECIFICATORS, fspec->type)) {
    if ((int)s_len < fspec->precision) {
      zero = fspec->precision - s_len;
      if (fspec->type == 'o' && fspec->fl.hash)
        zero -= prefix_symbol_len(fspec);
    }
    if (fspec->fl.zero && fspec->precision == -1)
      zero = fspec->width - s_len - prefix_symbol_len(fspec);
  } else if (s21_strchr(FLOAT_SPECIFICATORS, fspec->type) && fspec->fl.zero) {
    zero = fspec->width - s_len - prefix_symbol_len(fspec);
  }
  return zero;
}

void int_to_str(char *buffer, long long int num, Format *fspec) {
  char *ptr = buffer;
  if (num == 0) {
    *(ptr++) = '0';
  }
  if (num < 0) {
    num *= -1;
    fspec->is_negative = 1;
  }
  while (num > 0) {
    *ptr++ = (num % 10) + '0';
    num /= 10;
  }
  *ptr = '\0';
  reverse_str(buffer);
}

void uint_to_str(char *buffer, long unsigned int num, char type) {
  char *ptr = buffer;
  char base = 10, shift = 0;
  if (type == 'X' || type == 'x' || type == 'p') {
    base = 16;
    shift = (type == 'X') ? 'A' - 10 : 'a' - 10;
  } else if (type == 'o')
    base = 8;
  while (num > 0) {
    char digit = num % base;
    *ptr++ = (digit < 10) ? digit + '0' : digit + shift;
    num /= base;
  }
  *ptr = '\0';
  reverse_str(buffer);
}

void reverse_str(char *str) {
  int len = s21_strlen(str);
  char *tmp = calloc(len, sizeof(char));
  if (tmp) {
    for (int i = 0; i < len; i++) tmp[i] = str[len - i - 1];
    for (int i = 0; i < len; i++) str[i] = tmp[i];
    free(tmp);
  } else {
    fprintf(stderr, "ERROR: Memory allocation failed (reverse_str)\n");
  }
}

void float_to_str(char *buffer, long double num, Format *fspec) {
  int prec = fspec->precision;
  int exp = 0, offset = 0;
  if (num < 0) {
    num = -num;
    fspec->is_negative = 1;
  }
  f_to_str(buffer, num, &exp);
  offset = offset_calc(exp, prec, fspec->type);
  s21_size_t len = s21_strlen(buffer);
  sprint_symbols(buffer + len, offset - len, '0');
  round_str(buffer, offset, &exp);
  if (s21_strchr("eE", fspec->type)) {
    str_format_e(buffer, exp, fspec);
  } else if (fspec->type == 'f')
    str_format_f(buffer, exp, fspec);
  else if (s21_strchr("gG", fspec->type)) {
    str_format_g(buffer, exp, offset, fspec);
  }
}

void f_to_str(char *buffer, long double num, int *exp) {
  long double divider = 1.0L;
  char *ptr = buffer;
  *exp = -1;
  while (num >= divider * 10.0L) {
    divider *= 10;
  }
  while (divider > 0.11) {
    long double div = num / divider;
    int digit = (int)div;
    *(ptr++) = digit + '0';
    num = num - digit * divider;
    divider /= 10;
    (*exp)++;
  }
  if (buffer[0] == '0') *exp = -1;
  *(ptr++) = '.';
  char exp_flag = (*exp >= 0) ? 1 : 0;

  for (int i = 0; i < 150 && num * 10 > 1e-15; i++) {
    num *= 10.0L;
    int digit = (int)num;
    if (!exp_flag && digit != 0) {
      (*exp) = -i - 1;
      exp_flag = 1;
    }
    *(ptr++) = digit + '0';
    num -= digit;
  }
}

int offset_calc(int exp, int precision, char type) {
  int offset = precision + 1;
  if (type == 'f')
    offset += (exp > 0) ? exp + 1 : 1;
  else {
    if (exp < 0) {
      offset += (1 - exp);
    } else if (precision > exp) {
      offset += 1;
    }
    if (type == 'g' || type == 'G')
      if (precision != 0) offset -= 1;
  }
  return offset;
}

void right_shift(char *buffer) {
  s21_size_t length = s21_strlen(buffer);
  for (s21_size_t i = length; i > 0; i--) {
    buffer[i] = buffer[i - 1];
  }
  buffer[0] = 1 + '0';
}

void round_str(char *buffer, int offset, int *exp) {
  char *ptr = buffer + offset;
  if (*ptr != 0) {
    if (*ptr == '.') ptr++;
    if (*ptr >= '5') {
      do {
        ptr--;
        if (*ptr == '.') ptr--;
        *ptr = (*(ptr) - '0' + 1) % 10 + '0';
      } while (*ptr == '0' && ptr - buffer > 0);
      int pos = ptr - buffer;
      if (*ptr == '1' && (pos == (*exp) * -1 || pos == 0)) (*exp)++;
      if (ptr == buffer && *ptr == '0') {
        right_shift(buffer);
        (*exp)++;
      }
    }
  }
}

void str_format_e(char *buffer, int exp, Format *fspec) {
  int prec = fspec->precision;
  s21_size_t len = s21_strlen(buffer);
  char temp_buffer[MAX_NUM_LEN] = {0};
  s21_memcpy(temp_buffer, buffer, len);
  s21_size_t b = 0, t = 0;
  s21_size_t end = (prec != 0) ? prec + 2 : prec + 1;
  if (s21_strchr("gG", fspec->type) && prec != 0) end -= 1;
  if (exp < 0) t += 1 + exp * -1;
  for (; t < len && b < end;) {
    if (b == 1) buffer[b++] = '.';
    if (temp_buffer[t] == '.') t++;
    buffer[b++] = temp_buffer[t++];
  }
  buffer[end] = '\0';
  if (fspec->fl.hash && !s21_strchr(buffer, '.')) buffer[b++] = '.';
  buffer[b++] = (fspec->type == 'e' || fspec->type == 'g') ? 'e' : 'E';
  buffer[b++] = (exp >= 0) ? '+' : '-';
  if (exp < 0) exp *= -1;
  if (exp <= 9) {
    buffer[b++] = '0';
  }
  int_to_str(buffer + b, exp, fspec);
}

void str_format_f(char *buffer, int exp, const Format *fspec) {
  int end = 0;
  if (s21_strchr("gG", fspec->type)) {
    end = fspec->precision;
    if (exp < 0) end += -exp;
  } else {
    while (buffer[end] && buffer[end] != '.') end++;
    end += fspec->precision;
  }
  buffer[end + 1] = '\0';
  end = s21_strlen(buffer) - 1;
  if (!fspec->fl.hash && buffer[end] == '.') buffer[end] = '\0';
}

void str_format_g(char *buffer, int exp, int offset, Format *fspec) {
  if ((exp >= fspec->precision && exp != 0) || exp < -4) {
    if (!fspec->fl.hash) cut_zero_for_g(buffer, offset, 1);
    str_format_e(buffer, exp, fspec);
  } else {
    if (!fspec->fl.hash) cut_zero_for_g(buffer, offset, 0);
    str_format_f(buffer, exp, fspec);
  }
  fspec->precision = 0;
}

void cut_zero_for_g(char *buffer, int end, int flag_e) {
  buffer[end] = '\0';
  if (s21_strchr(buffer, '.')) flag_e = 1;
  s21_size_t i = s21_strlen(buffer) - 1;
  for (; flag_e && buffer[i] == '0'; i--) {
    buffer[i] = '\0';
  }
}
