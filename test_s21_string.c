#include "test_s21_string.h"

// memchr
START_TEST(test_memchr_found) {
  char str[] = SAMPLE_STRING;
  char *s21_result = s21_memchr(str, CHAR_TO_FIND, strlen(str));
  char *std_result = memchr(str, CHAR_TO_FIND, strlen(str));
  ck_assert_ptr_ne(s21_result, NULL);
  ck_assert_ptr_ne(std_result, NULL);
  ck_assert_ptr_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_memchr_not_found) {
  char str[] = SAMPLE_STRING;
  char *s21_result = s21_memchr(str, CHAR_NOT_FOUND, strlen(str));
  char *std_result = memchr(str, CHAR_NOT_FOUND, strlen(str));
  ck_assert_ptr_eq(s21_result, NULL);
  ck_assert_ptr_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_memchr_empty_str) {
  char str[] = EMPTY_STRING;
  char *s21_result = s21_memchr(str, CHAR_TO_FIND, strlen(str));
  char *std_result = memchr(str, CHAR_TO_FIND, strlen(str));
  ck_assert_ptr_eq(s21_result, NULL);
  ck_assert_ptr_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_memchr_zero_length) {
  char str[] = SAMPLE_STRING;
  char *s21_result = s21_memchr(str, CHAR_TO_FIND, 0);
  char *std_result = memchr(str, CHAR_TO_FIND, 0);
  ck_assert_ptr_eq(s21_result, NULL);
  ck_assert_ptr_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_memchr_out_of_set_length) {
  char str[] = SAMPLE_STRING;
  char c = str[strlen(str) - 1];
  size_t n = strlen(str) / 2;
  char *s21_result = s21_memchr(str, c, n);
  char *std_result = memchr(str, c, n);
  ck_assert_ptr_eq(s21_result, NULL);
  ck_assert_ptr_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_memchr_first_char) {
  char str[] = SAMPLE_STRING;
  char c = str[0];
  char *s21_result = s21_memchr(str, c, strlen(str));
  char *std_result = memchr(str, c, strlen(str));
  ck_assert_ptr_ne(s21_result, NULL);
  ck_assert_ptr_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_memchr_last_char) {
  char str[] = SAMPLE_STRING;
  char c = str[strlen(str) - 1];
  char *s21_result = s21_memchr(str, c, strlen(str));
  char *std_result = memchr(str, c, strlen(str));
  ck_assert_ptr_ne(s21_result, NULL);
  ck_assert_ptr_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_memchr_special_chars) {
  char str[] = SPECIAL_CHARS_STRING;
  char c = '!';
  char *s21_result = s21_memchr(str, c, strlen(str));
  char *std_result = memchr(str, c, strlen(str));
  ck_assert_ptr_ne(s21_result, NULL);
  ck_assert_ptr_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_memchr_non_printable) {
  char str[] = NON_PRINTABLE_STRING;
  char c = CHAR_NON_PRINTABLE;
  char *s21_result = s21_memchr(str, c, strlen(str));
  char *std_result = memchr(str, c, strlen(str));
  ck_assert_ptr_ne(s21_result, NULL);
  ck_assert_ptr_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_memchr_extended_ascii) {
  char str[] = EXTENDED_ASCII_STRING;
  unsigned char c = EXTENDED_ASCII_CHAR;
  char *s21_result = s21_memchr(str, c, strlen(str));
  char *std_result = memchr(str, c, strlen(str));
  ck_assert_ptr_ne(s21_result, NULL);
  ck_assert_ptr_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_memchr_hex_bytes) {
  unsigned char str[] = {0xa1, 0xb2, 0xc3, 0xd4, 0xe5, 0xf6,
                         's',  'a',  'm',  'p',  'l',  'e'};
  char c = CHAR_TO_FIND;
  size_t n = sizeof(str);
  char *s21_result = s21_memchr(str, c, n);
  char *std_result = memchr(str, c, n);
  ck_assert_ptr_ne(s21_result, NULL);
  ck_assert_ptr_eq(s21_result, std_result);
}
END_TEST

// memcmp
START_TEST(test_memcmp_equal) {
  char str1[] = SAMPLE_STRING;
  char str2[] = SAMPLE_STRING;
  int s21_result = s21_memcmp(str1, str2, strlen(str1));
  int std_result = memcmp(str1, str2, strlen(str1));
  ck_assert_int_eq(s21_result, 0);
  ck_assert_int_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_memcmp_different) {
  char str1[] = SAMPLE_STRING;
  char str2[] = BIGGER_STRING;
  int s21_result = s21_memcmp(str1, str2, strlen(str1));
  int std_result = memcmp(str1, str2, strlen(str1));
  ck_assert_int_gt(s21_result, 0);
  ck_assert_int_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_memcmp_mid_length) {
  char str1[] = SAMPLE_STRING;
  char str2[] = SAMPLE_STRING;
  size_t n = strlen(str1) / 2;
  int s21_result = s21_memcmp(str1, str2, n);
  int std_result = memcmp(str1, str2, n);
  ck_assert_int_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_memcmp_zero_length) {
  char str1[] = SAMPLE_STRING;
  char str2[] = SAMPLE_STRING;
  int s21_result = s21_memcmp(str1, str2, 0);
  int std_result = memcmp(str1, str2, 0);
  ck_assert_int_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_memcmp_null_bytes) {
  char str1[] = STRING_WITH_MULTIPLE_NULLS;
  char str2[] = STRING_WITH_MULTIPLE_NULLS;
  size_t n = sizeof(str1);
  int s21_result = s21_memcmp(str1, str2, n);
  int std_result = memcmp(str1, str2, n);
  ck_assert_int_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_memcmp_extended_ascii) {
  unsigned char str1[] = EXTENDED_ASCII_STRING;
  unsigned char str2[] = EXTENDED_ASCII_STRING;
  size_t n = sizeof(str1);
  int s21_result = s21_memcmp(str1, str2, n);
  int std_result = memcmp(str1, str2, n);
  ck_assert_int_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_memcmp_large_data) {
  char *str1 = malloc(LARGE_SIZE * sizeof(char));
  char *str2 = malloc(LARGE_SIZE * sizeof(char));
  if (str1 == NULL || str2 == NULL) {
    ck_abort_msg("malloc failed");
  }
  memset(str1, '!', LARGE_SIZE);
  memset(str2, '!', LARGE_SIZE);
  int s21_result = s21_memcmp(str1, str2, LARGE_SIZE);
  int std_result = memcmp(str1, str2, LARGE_SIZE);
  ck_assert_int_eq(s21_result, std_result);
  free(str1);
  free(str2);
}
END_TEST

// memcpy
START_TEST(test_memcpy_full) {
  char src[] = SAMPLE_STRING;
  char s21_dest[strlen(src) + 1];
  char std_dest[strlen(src) + 1];
  memset(s21_dest, 0, sizeof(s21_dest));
  memset(std_dest, 0, sizeof(std_dest));
  size_t n = strlen(src);
  s21_memcpy(s21_dest, src, n);
  memcpy(std_dest, src, n);
  ck_assert_mem_eq(s21_dest, std_dest, sizeof(s21_dest));
}
END_TEST

START_TEST(test_memcpy_partial) {
  char src[] = SAMPLE_STRING;
  char s21_dest[strlen(src) + 1];
  char std_dest[strlen(src) + 1];
  memset(s21_dest, 0, sizeof(s21_dest));
  memset(std_dest, 0, sizeof(std_dest));
  size_t n = strlen(src) / 2;
  s21_memcpy(s21_dest, src, n);
  memcpy(std_dest, src, n);
  ck_assert_mem_eq(s21_dest, std_dest, sizeof(s21_dest));
}
END_TEST

START_TEST(test_memcpy_zero) {
  char src[] = SAMPLE_STRING;
  char s21_dest[strlen(src) + 1];
  char std_dest[strlen(src) + 1];
  memset(s21_dest, 0, sizeof(s21_dest));
  memset(std_dest, 0, sizeof(std_dest));
  size_t n = 0;
  s21_memcpy(s21_dest, src, n);
  memcpy(std_dest, src, n);
  ck_assert_mem_eq(s21_dest, std_dest, sizeof(s21_dest));
}
END_TEST

START_TEST(test_memcpy_one_byte) {
  char src[] = SAMPLE_STRING;
  char s21_dest[strlen(src) + 1];
  char std_dest[strlen(src) + 1];
  memset(s21_dest, 0, sizeof(s21_dest));
  memset(std_dest, 0, sizeof(std_dest));
  size_t n = 1;
  s21_memcpy(s21_dest, src, n);
  memcpy(std_dest, src, n);
  ck_assert_mem_eq(s21_dest, std_dest, sizeof(s21_dest));
}
END_TEST

START_TEST(test_memcpy_str_with_null_term) {
  char src[] = STRING_WITH_NULL;
  char s21_dest[sizeof(src)];
  char std_dest[sizeof(src)];
  memset(s21_dest, 0, sizeof(s21_dest));
  memset(std_dest, 0, sizeof(std_dest));
  size_t n = sizeof(src);
  s21_memcpy(s21_dest, src, n);
  memcpy(std_dest, src, n);
  ck_assert_mem_eq(s21_dest, std_dest, sizeof(s21_dest));
}
END_TEST

START_TEST(test_memcpy_large_data) {
  char *src = malloc(LARGE_SIZE);
  char *s21_dest = malloc(LARGE_SIZE);
  char *std_dest = malloc(LARGE_SIZE);
  if (src == NULL || s21_dest == NULL || std_dest == NULL) {
    ck_abort_msg("malloc failed");
  }
  memset(src, '!', LARGE_SIZE);
  memset(s21_dest, 0, LARGE_SIZE);
  memset(std_dest, 0, LARGE_SIZE);
  size_t n = LARGE_SIZE;
  s21_memcpy(s21_dest, src, n);
  memcpy(std_dest, src, n);
  ck_assert_mem_eq(s21_dest, std_dest, LARGE_SIZE);
  free(src);
  free(s21_dest);
  free(std_dest);
}
END_TEST

// memset
START_TEST(test_memset_full) {
  char s21_str[] = SAMPLE_STRING;
  char std_str[] = SAMPLE_STRING;
  size_t n = strlen(s21_str);
  s21_memset(s21_str, CHAR_NOT_FOUND, n);
  memset(std_str, CHAR_NOT_FOUND, n);
  ck_assert_str_eq(s21_str, std_str);
}
END_TEST

START_TEST(test_memset_partial) {
  char s21_str[] = SAMPLE_STRING;
  char std_str[] = SAMPLE_STRING;
  size_t n = strlen(s21_str) / 2;
  s21_memset(s21_str, CHAR_NOT_FOUND, n);
  memset(std_str, CHAR_NOT_FOUND, n);
  ck_assert_str_eq(s21_str, std_str);
}
END_TEST

START_TEST(test_memset_zero) {
  char s21_str[] = SAMPLE_STRING;
  char std_str[] = SAMPLE_STRING;
  size_t n = 0;
  s21_memset(s21_str, CHAR_NOT_FOUND, n);
  ck_assert_str_eq(s21_str, std_str);
  memset(std_str, CHAR_NOT_FOUND, n);
  ck_assert_str_eq(s21_str, std_str);
}
END_TEST

START_TEST(test_memset_str_with_null_term) {
  char s21_str[] = STRING_WITH_NULL;
  char std_str[] = STRING_WITH_NULL;
  size_t n = sizeof(s21_str);
  s21_memset(s21_str, CHAR_NOT_FOUND, n - 1);
  memset(std_str, CHAR_NOT_FOUND, n - 1);
  ck_assert_str_eq(s21_str, std_str);
}
END_TEST

START_TEST(test_memset_extended_ascii_char) {
  char s21_str[] = SAMPLE_STRING;
  char std_str[] = SAMPLE_STRING;
  size_t n = strlen(s21_str);
  s21_memset(s21_str, EXTENDED_ASCII_CHAR, n);
  memset(std_str, EXTENDED_ASCII_CHAR, n);
  ck_assert_mem_eq(s21_str, std_str, sizeof(s21_str));
}
END_TEST

START_TEST(test_memset_very_large_data) {
  char *s21_str = calloc(LARGE_SIZE, sizeof(char));
  char *std_str = calloc(LARGE_SIZE, sizeof(char));
  if (s21_str == NULL || std_str == NULL) {
    ck_abort_msg("calloc failed");
  }
  size_t n = LARGE_SIZE - 1;
  s21_memset(s21_str, CHAR_NOT_FOUND, n);
  memset(std_str, CHAR_NOT_FOUND, n);
  ck_assert_mem_eq(s21_str, std_str, LARGE_SIZE);
  free(s21_str);
  free(std_str);
}
END_TEST

// strncat
START_TEST(test_strncat_full) {
  char s21_dest[strlen(SAMPLE_STRING) * 2 + 1];
  char std_dest[strlen(SAMPLE_STRING) * 2 + 1];
  memset(s21_dest, 0, sizeof(s21_dest));
  memset(std_dest, 0, sizeof(std_dest));
  size_t n = strlen(SAMPLE_STRING);
  s21_strncat(s21_dest, SAMPLE_STRING, n);
  strncat(std_dest, SAMPLE_STRING, n);
  ck_assert_str_eq(s21_dest, std_dest);
}
END_TEST

START_TEST(test_strncat_partial) {
  char s21_dest[strlen(SAMPLE_STRING) * 2 + 1];
  char std_dest[strlen(SAMPLE_STRING) * 2 + 1];
  memset(s21_dest, 0, sizeof(s21_dest));
  memset(std_dest, 0, sizeof(std_dest));
  size_t n = strlen(SAMPLE_STRING) / 2;
  s21_strncat(s21_dest, SAMPLE_STRING, n);
  strncat(std_dest, SAMPLE_STRING, n);
  ck_assert_str_eq(s21_dest, std_dest);
}
END_TEST

START_TEST(test_strncat_zero) {
  char s21_dest[strlen(SAMPLE_STRING) * 2 + 1];
  char std_dest[strlen(SAMPLE_STRING) * 2 + 1];
  memset(s21_dest, 0, sizeof(s21_dest));
  memset(std_dest, 0, sizeof(std_dest));
  size_t n = 0;
  s21_strncat(s21_dest, SAMPLE_STRING, n);
  ck_assert_str_eq(s21_dest, std_dest);
  strncat(std_dest, SAMPLE_STRING, n);
  ck_assert_str_eq(s21_dest, std_dest);
}
END_TEST

START_TEST(test_strncat_out_of_range_n) {
  char s21_dest[strlen(SAMPLE_STRING) * 3 + 1];
  char std_dest[strlen(SAMPLE_STRING) * 3 + 1];
  strcpy(s21_dest, SAMPLE_STRING);
  strcpy(std_dest, SAMPLE_STRING);
  size_t n = strlen(SAMPLE_STRING) * 2;
  s21_strncat(s21_dest, SAMPLE_STRING, n);
  strncat(std_dest, SAMPLE_STRING, n);
  ck_assert_str_eq(s21_dest, std_dest);
}
END_TEST

START_TEST(test_strncat_empty_src) {
  char s21_dest[strlen(SAMPLE_STRING) * 2 + 1];
  char std_dest[strlen(SAMPLE_STRING) * 2 + 1];
  strcpy(s21_dest, SAMPLE_STRING);
  strcpy(std_dest, SAMPLE_STRING);
  char src[] = EMPTY_STRING;
  size_t n = strlen(src);
  s21_strncat(s21_dest, src, n);
  strncat(std_dest, src, n);
  ck_assert_str_eq(s21_dest, std_dest);
}
END_TEST

START_TEST(test_strncat_src_with_null_term) {
  char s21_dest[strlen(SAMPLE_STRING) * 3 + 1];
  char std_dest[strlen(SAMPLE_STRING) * 3 + 1];
  strcpy(s21_dest, SAMPLE_STRING);
  strcpy(std_dest, SAMPLE_STRING);
  char src[] = STRING_WITH_NULL;
  size_t n = sizeof(src);
  s21_strncat(s21_dest, src, n);
  strncat(std_dest, src, n);
  ck_assert_str_eq(s21_dest, std_dest);
}
END_TEST

START_TEST(test_strncat_very_large_src) {
  char *s21_dest = calloc(LARGE_SIZE + 1, sizeof(char));
  char *std_dest = calloc(LARGE_SIZE + 1, sizeof(char));
  if (s21_dest == NULL || std_dest == NULL) {
    ck_abort_msg("calloc failed");
  }
  char *src = malloc(LARGE_SIZE);
  if (src == NULL) {
    ck_abort_msg("malloc failed");
  }
  memset(src, '!', LARGE_SIZE);
  size_t n = LARGE_SIZE;
  s21_strncat(s21_dest, src, n);
  strncat(std_dest, src, n);
  ck_assert_str_eq(s21_dest, std_dest);
  free(s21_dest);
  free(std_dest);
  free(src);
}
END_TEST

// strchr
START_TEST(test_strchr_found) {
  char str[] = SAMPLE_STRING;
  char *s21_result = s21_strchr(str, CHAR_TO_FIND);
  char *std_result = strchr(str, CHAR_TO_FIND);
  ck_assert_ptr_ne(s21_result, NULL);
  ck_assert_ptr_ne(std_result, NULL);
  ck_assert_ptr_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_strchr_not_found) {
  char str[] = SAMPLE_STRING;
  char *s21_result = s21_strchr(str, CHAR_NOT_FOUND);
  char *std_result = strchr(str, CHAR_NOT_FOUND);
  ck_assert_ptr_eq(s21_result, NULL);
  ck_assert_ptr_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_strchr_searching_null_term) {
  char str[] = STRING_WITH_NULL;
  char *s21_result = s21_strchr(str, '\0');
  char *std_result = strchr(str, '\0');
  ck_assert_ptr_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_strchr_empty_str) {
  char str[] = EMPTY_STRING;
  char *s21_result = s21_strchr(str, CHAR_TO_FIND);
  char *std_result = strchr(str, CHAR_TO_FIND);
  ck_assert_ptr_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_strchr_extended_ascii) {
  unsigned char str[] = EXTENDED_ASCII_STRING;
  char *s21_result = s21_strchr((char *)str, EXTENDED_ASCII_CHAR);
  char *std_result = strchr((char *)str, EXTENDED_ASCII_CHAR);
  ck_assert_ptr_eq(s21_result, std_result);
}
END_TEST

// strncmp
START_TEST(test_strncmp_equal) {
  char str1[] = SAMPLE_STRING;
  char str2[] = SAMPLE_STRING;
  size_t n = strlen(str1);
  int s21_result = s21_strncmp(str1, str2, n);
  int std_result = strncmp(str1, str2, n);
  ck_assert_int_eq(s21_result, 0);
  ck_assert_int_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_strncmp_different) {
  char str1[] = SAMPLE_STRING;
  char str2[] = BIGGER_STRING;
  size_t n = strlen(str2);
  int s21_result = s21_strncmp(str1, str2, n);
  int std_result = strncmp(str1, str2, n);
  ck_assert_int_gt(s21_result, 0);
  ck_assert_int_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_strncmp_mid_range_length) {
  char str1[] = SAMPLE_STRING;
  char str2[] = STRING_W_TRAILING_COMA_DELIM;
  size_t n = strlen(str1) / 2;
  int s21_result = s21_strncmp(str1, str2, n);
  int std_result = strncmp(str1, str2, n);
  ck_assert_int_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_strncmp_zero_length) {
  char str1[] = SAMPLE_STRING;
  char str2[] = SAMPLE_STRING;
  size_t n = 0;
  int s21_result = s21_strncmp(str1, str2, n);
  int std_result = strncmp(str1, str2, n);
  ck_assert_int_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_strncmp_out_of_range_length) {
  char str1[] = SAMPLE_STRING;
  char str2[] = SAMPLE_STRING;
  size_t n = strlen(str1) * 2;
  int s21_result = s21_strncmp(str1, str2, n);
  int std_result = strncmp(str1, str2, n);
  ck_assert_int_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_strncmp_empty_str) {
  char str1[] = EMPTY_STRING;
  char str2[] = EMPTY_STRING;
  size_t n = 1;
  int s21_result = s21_strncmp(str1, str2, n);
  int std_result = strncmp(str1, str2, n);
  ck_assert_int_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_strncmp_str_with_null_term) {
  char str1[] = STRING_WITH_NULL;
  char str2[] = STRING_WITH_NULL;
  size_t n = sizeof(str1);
  int s21_result = s21_strncmp(str1, str2, n);
  int std_result = strncmp(str1, str2, n);
  ck_assert_int_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_strncmp_extended_ascii) {
  unsigned char str1[] = EXTENDED_ASCII_STRING;
  unsigned char str2[] = EXTENDED_ASCII_STRING;
  size_t n = sizeof(str1);
  int s21_result = s21_strncmp((char *)str1, (char *)str2, n);
  int std_result = strncmp((char *)str1, (char *)str2, n);
  ck_assert_int_eq(s21_result, std_result);
}
END_TEST

// strncpy
START_TEST(test_strncpy_full) {
  char s21_dest[strlen(SAMPLE_STRING) + 1];
  char std_dest[strlen(SAMPLE_STRING) + 1];
  memset(s21_dest, 0, sizeof(s21_dest));
  memset(std_dest, 0, sizeof(std_dest));
  size_t n = strlen(SAMPLE_STRING);
  s21_strncpy(s21_dest, SAMPLE_STRING, n);
  strncpy(std_dest, SAMPLE_STRING, n);
  ck_assert_str_eq(s21_dest, std_dest);
}
END_TEST

START_TEST(test_strncpy_partial) {
  char s21_dest[strlen(SAMPLE_STRING) + 1];
  char std_dest[strlen(SAMPLE_STRING) + 1];
  memset(s21_dest, 0, sizeof(s21_dest));
  memset(std_dest, 0, sizeof(std_dest));
  size_t n = strlen(SAMPLE_STRING) / 2;
  s21_strncpy(s21_dest, SAMPLE_STRING, n);
  strncpy(std_dest, SAMPLE_STRING, n);
  ck_assert_str_eq(s21_dest, std_dest);
}
END_TEST

START_TEST(test_strncpy_zero) {
  char s21_dest[strlen(SAMPLE_STRING) + 1];
  char std_dest[strlen(SAMPLE_STRING) + 1];
  memset(s21_dest, 0, sizeof(s21_dest));
  memset(std_dest, 0, sizeof(std_dest));
  size_t n = 0;
  s21_strncpy(s21_dest, SAMPLE_STRING, n);
  ck_assert_str_eq(s21_dest, std_dest);
  strncpy(std_dest, SAMPLE_STRING, n);
  ck_assert_str_eq(s21_dest, std_dest);
}
END_TEST

START_TEST(test_strncpy_src_shorter_then_n) {
  char s21_dest[strlen(BIGGER_STRING)];
  char std_dest[strlen(BIGGER_STRING)];
  memset(s21_dest, 0, sizeof(s21_dest));
  memset(std_dest, 0, sizeof(std_dest));
  char src[] = SAMPLE_STRING;
  size_t n = strlen(s21_dest);
  s21_strncpy(s21_dest, src, n);
  strncpy(std_dest, src, n);
  ck_assert_str_eq(s21_dest, std_dest);
}
END_TEST

START_TEST(test_strncpy_src_longer_then_n) {
  char s21_dest[strlen(SAMPLE_STRING) + 1];
  char std_dest[strlen(SAMPLE_STRING) + 1];
  memset(s21_dest, 0, sizeof(s21_dest));
  memset(std_dest, 0, sizeof(std_dest));
  char src[] = BIGGER_STRING;
  size_t n = strlen(SAMPLE_STRING);
  s21_strncpy(s21_dest, src, n);
  strncpy(std_dest, src, n);
  ck_assert_str_eq(s21_dest, std_dest);
}
END_TEST

START_TEST(test_strncpy_src_with_null_term) {
  char s21_dest[sizeof(STRING_WITH_NULL)];
  char std_dest[sizeof(STRING_WITH_NULL)];
  size_t n = sizeof(STRING_WITH_NULL);
  memset(s21_dest, 0, n);
  memset(std_dest, 0, n);
  s21_strncpy(s21_dest, STRING_WITH_NULL, n);
  strncpy(std_dest, STRING_WITH_NULL, n);
  ck_assert_str_eq(s21_dest, std_dest);
}
END_TEST

START_TEST(test_strncpy_src_with_special_chars) {
  char s21_dest[sizeof(SPECIAL_CHARS_STRING)];
  char std_dest[sizeof(SPECIAL_CHARS_STRING)];
  size_t n = sizeof(SPECIAL_CHARS_STRING);
  memset(s21_dest, 0, n);
  memset(std_dest, 0, n);
  s21_strncpy(s21_dest, SPECIAL_CHARS_STRING, n);
  strncpy(std_dest, SPECIAL_CHARS_STRING, n);
  ck_assert_str_eq(s21_dest, std_dest);
}
END_TEST

START_TEST(test_strncpy_src_with_non_printable) {
  char s21_dest[sizeof(NON_PRINTABLE_STRING)];
  char std_dest[sizeof(NON_PRINTABLE_STRING)];
  size_t n = sizeof(NON_PRINTABLE_STRING);
  memset(s21_dest, 0, n);
  memset(std_dest, 0, n);
  s21_strncpy(s21_dest, NON_PRINTABLE_STRING, n);
  strncpy(std_dest, NON_PRINTABLE_STRING, n);
  ck_assert_str_eq(s21_dest, std_dest);
}
END_TEST

START_TEST(test_strncpy_src_with_extended_ascii) {
  size_t n = strlen(EXTENDED_ASCII_STRING);
  char s21_dest[n + 1];
  char std_dest[n + 1];
  memset(s21_dest, 0, sizeof(s21_dest));
  memset(std_dest, 0, sizeof(std_dest));
  s21_strncpy(s21_dest, EXTENDED_ASCII_STRING, n);
  strncpy(std_dest, EXTENDED_ASCII_STRING, n);
  ck_assert_str_eq(s21_dest, std_dest);
}
END_TEST

START_TEST(test_strncpy_very_large_data) {
  size_t n = LARGE_SIZE;
  char *src = malloc(n - 1);
  char *s21_dest = calloc(n, sizeof(char));
  char *std_dest = calloc(n, sizeof(char));
  if (src == NULL || s21_dest == NULL || std_dest == NULL) {
    ck_abort_msg("calloc failed");
  }
  memset(src, '!', n - 1);
  s21_strncpy(s21_dest, src, n - 1);
  strncpy(std_dest, src, n - 1);
  ck_assert_str_eq(s21_dest, std_dest);
  free(src);
  free(s21_dest);
  free(std_dest);
}
END_TEST

// strcspn
START_TEST(test_strcspn_found) {
  char str1[] = SAMPLE_STRING;
  char str2[] = ONE_IN_SAMPLE;
  size_t s21_result = s21_strcspn(str1, str2);
  size_t std_result = strcspn(str1, str2);
  ck_assert_int_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_strcspn_not_found) {
  char str1[] = SAMPLE_STRING;
  char str2[] = NONE_IN_SAMPLE;
  size_t s21_result = s21_strcspn(str1, str2);
  size_t std_result = strcspn(str1, str2);
  ck_assert_int_eq(s21_result, strlen(str1));
  ck_assert_int_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_strcspn_empty_str1) {
  char str1[] = EMPTY_STRING;
  char str2[] = ONE_IN_SAMPLE;
  size_t s21_result = s21_strcspn(str1, str2);
  size_t std_result = strcspn(str1, str2);
  ck_assert_int_eq(s21_result, 0);
  ck_assert_int_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_strcspn_empty_str2) {
  char str1[] = SAMPLE_STRING;
  char str2[] = EMPTY_STRING;
  size_t s21_result = s21_strcspn(str1, str2);
  size_t std_result = strcspn(str1, str2);
  ck_assert_int_eq(s21_result, strlen(str1));
  ck_assert_int_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_strcspn_empty_both) {
  char str1[] = EMPTY_STRING;
  char str2[] = EMPTY_STRING;
  size_t s21_result = s21_strcspn(str1, str2);
  size_t std_result = strcspn(str1, str2);
  ck_assert_int_eq(s21_result, 0);
  ck_assert_int_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_strcspn_multiple_occurances) {
  char str1[] = SAMPLE_STRING;
  char str2[] = WORD_IN_SAMPLE_TWICE;
  size_t s21_result = s21_strcspn(str1, str2);
  size_t std_result = strcspn(str1, str2);
  ck_assert_int_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_strcspn_special_chars) {
  char str1[] = SPECIAL_CHARS_STRING;
  char str2[] = WORD_IN_SAMPLE_SPECIAL_CHARS;
  size_t s21_result = s21_strcspn(str1, str2);
  size_t std_result = strcspn(str1, str2);
  ck_assert_int_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_strcspn_non_printable_str1) {
  char str1[] = NON_PRINTABLE_STRING;
  char str2[] = WORD_IN_SAMPLE;
  size_t s21_result = s21_strcspn(str1, str2);
  size_t std_result = strcspn(str1, str2);
  ck_assert_int_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_strcspn_non_printable_str2) {
  char str1[] = SAMPLE_STRING;
  char str2[] = WORD_IN_SAMPLE_NON_PRINTABLE;
  size_t s21_result = s21_strcspn(str1, str2);
  size_t std_result = strcspn(str1, str2);
  ck_assert_int_eq(s21_result, std_result);
}
END_TEST

// strerror
START_TEST(test_strerror_basic) {
  for (int errno = 0; errno < 107; errno++) {
    char *s21_result = s21_strerror(errno);
    char *std_result = strerror(errno);
    ck_assert_str_eq(s21_result, std_result);
  }
}
END_TEST

START_TEST(test_strerror_negative) {
  for (int errno = -10; errno < 0; errno++) {
    char *s21_result = s21_strerror(errno);
    char *std_result = strerror(errno);
  }
}
END_TEST

START_TEST(test_strerror_large_positive) {
  for (int errno = 107; errno < 1000; errno++) {
    char *s21_result = s21_strerror(errno);
    char *std_result = strerror(errno);
    ck_assert_str_eq(s21_result, std_result);
  }
}
END_TEST

// strlen
START_TEST(test_strlen_basic) {
  char str[] = SAMPLE_STRING;
  size_t s21_result = s21_strlen(str);
  size_t std_result = strlen(str);
  ck_assert_int_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_strlen_empty) {
  char str[] = EMPTY_STRING;
  size_t s21_result = s21_strlen(str);
  size_t std_result = strlen(str);
  ck_assert_int_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_strlen_str_with_null_term) {
  char str[] = STRING_WITH_NULL;
  size_t s21_result = s21_strlen(str);
  size_t std_result = strlen(str);
  ck_assert_int_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_strlen_extended_ascii) {
  unsigned char str[] = EXTENDED_ASCII_STRING;
  size_t s21_result = s21_strlen((const char *)str);
  size_t std_result = strlen((const char *)str);
  ck_assert_int_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_strlen_very_long_str) {
  char *str = malloc(LARGE_SIZE);
  if (str == NULL) {
    ck_abort_msg("malloc failed");
  }
  memset(str, 'a', sizeof(str) - 1);
  str[sizeof(str) - 1] = '\0';
  size_t s21_result = s21_strlen(str);
  size_t std_result = strlen(str);
  ck_assert_int_eq(s21_result, std_result);
  free(str);
}
END_TEST

START_TEST(test_strlen_multiple_null_terms) {
  char str[] = STRING_WITH_MULTIPLE_NULLS;
  size_t s21_result = s21_strlen(str);
  size_t std_result = strlen(str);
  ck_assert_int_eq(s21_result, std_result);
}
END_TEST

// strpbrk
START_TEST(test_strpbrk_found) {
  char str1[] = SAMPLE_STRING;
  char str2[] = ONE_IN_SAMPLE;
  char *s21_result = s21_strpbrk(str1, str2);
  char *std_result = strpbrk(str1, str2);
  ck_assert_ptr_ne(s21_result, NULL);
  ck_assert_ptr_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_strpbrk_not_found) {
  char str1[] = SAMPLE_STRING;
  char str2[] = NONE_IN_SAMPLE;
  char *s21_result = s21_strpbrk(str1, str2);
  char *std_result = strpbrk(str1, str2);
  ck_assert_ptr_eq(s21_result, NULL);
  ck_assert_ptr_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_strpbrk_multiple_occurances) {
  char str1[] = SAMPLE_STRING;
  char str2[] = WORD_IN_SAMPLE;
  char *s21_result = s21_strpbrk(str1, str2);
  char *std_result = strpbrk(str1, str2);
  ck_assert_ptr_ne(s21_result, NULL);
  ck_assert_ptr_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_strpbrk_empty_str1) {
  char str1[] = EMPTY_STRING;
  char str2[] = ONE_IN_SAMPLE;
  char *s21_result = s21_strpbrk(str1, str2);
  char *std_result = strpbrk(str1, str2);
  ck_assert_ptr_eq(s21_result, NULL);
  ck_assert_ptr_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_strpbrk_empty_str2) {
  char str1[] = SAMPLE_STRING;
  char str2[] = EMPTY_STRING;
  char *s21_result = s21_strpbrk(str1, str2);
  char *std_result = strpbrk(str1, str2);
  ck_assert_ptr_eq(s21_result, NULL);
  ck_assert_ptr_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_strpbrk_empty_both) {
  char str1[] = EMPTY_STRING;
  char str2[] = EMPTY_STRING;
  char *s21_result = s21_strpbrk(str1, str2);
  char *std_result = strpbrk(str1, str2);
  ck_assert_ptr_eq(s21_result, NULL);
  ck_assert_ptr_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_strpbrk_special_chars) {
  char str1[] = SPECIAL_CHARS_STRING;
  char str2[] = WORD_IN_SAMPLE_SPECIAL_CHARS;
  char *s21_result = s21_strpbrk(str1, str2);
  char *std_result = strpbrk(str1, str2);
  ck_assert_ptr_ne(s21_result, NULL);
  ck_assert_ptr_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_strpbrk_non_printable) {
  char str1[] = NON_PRINTABLE_STRING;
  char str2[] = WORD_IN_SAMPLE_NON_PRINTABLE;
  char *s21_result = s21_strpbrk(str1, str2);
  char *std_result = strpbrk(str1, str2);
  ck_assert_ptr_ne(s21_result, NULL);
  ck_assert_ptr_eq(s21_result, std_result);
}
END_TEST

// strrchr
START_TEST(test_strrchr_found) {
  char str[] = SAMPLE_STRING;
  char *s21_result = s21_strrchr(str, CHAR_TO_FIND);
  char *std_result = strrchr(str, CHAR_TO_FIND);
  ck_assert_ptr_ne(s21_result, NULL);
  ck_assert_ptr_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_strrchr_not_found) {
  char str[] = SAMPLE_STRING;
  char *s21_result = s21_strrchr(str, CHAR_NOT_FOUND);
  char *std_result = strrchr(str, CHAR_NOT_FOUND);
  ck_assert_ptr_eq(s21_result, NULL);
  ck_assert_ptr_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_strrchr_searching_null_term) {
  char str[] = STRING_WITH_NULL;
  char *s21_result = s21_strrchr(str, '\0');
  char *std_result = strrchr(str, '\0');
  ck_assert_ptr_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_strrchr_empty_str) {
  char str[] = EMPTY_STRING;
  char *s21_result = s21_strrchr(str, CHAR_TO_FIND);
  char *std_result = strrchr(str, CHAR_TO_FIND);
  ck_assert_ptr_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_strrchr_extended_ascii) {
  unsigned char str[] = EXTENDED_ASCII_STRING;
  char *s21_result = s21_strrchr((char *)str, EXTENDED_ASCII_CHAR);
  char *std_result = strrchr((char *)str, EXTENDED_ASCII_CHAR);
  ck_assert_ptr_eq(s21_result, std_result);
}
END_TEST

// strstr
START_TEST(test_strstr_found_basic) {
  char haystack[] = SAMPLE_STRING;
  char needle[] = WORD_IN_SAMPLE;
  char *s21_result = s21_strstr(haystack, needle);
  char *std_result = strstr(haystack, needle);
  ck_assert_ptr_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_strstr_not_found_basic) {
  char haystack[] = SAMPLE_STRING;
  char needle[] = NONE_IN_SAMPLE;
  char *s21_result = s21_strstr(haystack, needle);
  char *std_result = strstr(haystack, needle);
  ck_assert_ptr_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_strstr_found_at_start) {
  char haystack[] = SAMPLE_STRING;
  char needle[] = FIRST_WORD;
  char *s21_result = s21_strstr(haystack, needle);
  char *std_result = strstr(haystack, needle);
  ck_assert_ptr_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_strstr_found_at_end) {
  char haystack[] = SAMPLE_STRING;
  char needle[] = LAST_WORD;
  char *s21_result = s21_strstr(haystack, needle);
  char *std_result = strstr(haystack, needle);
  ck_assert_ptr_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_strstr_empty_haystack) {
  char haystack[] = EMPTY_STRING;
  char needle[] = WORD_IN_SAMPLE;
  char *s21_result = s21_strstr(haystack, needle);
  char *std_result = strstr(haystack, needle);
  ck_assert_ptr_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_strstr_empty_needle) {
  char haystack[] = SAMPLE_STRING;
  char needle[] = EMPTY_STRING;
  char *s21_result = s21_strstr(haystack, needle);
  char *std_result = strstr(haystack, needle);
  ck_assert_ptr_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_strstr_multiple_occurrences) {
  char haystack[] = SAMPLE_STRING;
  char needle[] = WORD_TWICE_IN_SAMPLE;
  char *s21_result = s21_strstr(haystack, needle);
  char *std_result = strstr(haystack, needle);
  ck_assert_ptr_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_strstr_extended_ascii) {
  unsigned char haystack[] = EXTENDED_ASCII_STRING;
  unsigned char needle[] = EXTENDED_ASCII_WORD;
  char *s21_result = s21_strstr((const char *)haystack, (const char *)needle);
  char *std_result = strstr((const char *)haystack, (const char *)needle);
  ck_assert_ptr_eq(s21_result, std_result);
}
END_TEST

// strtok
START_TEST(test_strtok_existing_delim) {
  char str[] = SAMPLE_STRING;
  char delim[] = DELIM;
  run_strtok_tests(str, delim);
}
END_TEST

START_TEST(test_strtok_non_existing_delim) {
  char str[] = SAMPLE_STRING;
  char delim[] = NOT_A_DELIM;
  run_strtok_tests(str, delim);
}
END_TEST

START_TEST(test_strtok_empty_string) {
  char str[] = EMPTY_STRING;
  char delim[] = DELIM;
  run_strtok_tests(str, delim);
}
END_TEST

START_TEST(test_strtok_empty_delim) {
  char str[] = SAMPLE_STRING;
  char delim[] = EMPTY_STRING;
  run_strtok_tests(str, delim);
}
END_TEST

START_TEST(test_strtok_consecutive_delim) {
  char str[] = STRING_W_CONSEC_COMA_DELIMS;
  char delim[] = COMA_DELIM;
  run_strtok_tests(str, delim);
}
END_TEST

START_TEST(test_strtok_leading_delim) {
  char str[] = STRING_W_LEADING_COMA_DELIM;
  char delim[] = COMA_DELIM;
  run_strtok_tests(str, delim);
}
END_TEST

START_TEST(test_strtok_trailing_delim) {
  char str[] = STRING_W_TRAILING_COMA_DELIM;
  char delim[] = COMA_DELIM;
  run_strtok_tests(str, delim);
}
END_TEST

START_TEST(test_strtok_mixed_delims) {
  char str[] = STRING_W_MIXED_DELIMS;
  char delim[] = MIXED_DELIMS;
  run_strtok_tests(str, delim);
}
END_TEST

START_TEST(test_strtok_only_delims_in_str) {
  char str[] = ONLY_COMAS_STRING;
  char delim[] = COMA_DELIM;
  run_strtok_tests(str, delim);
}
END_TEST

// s21_to_upper
START_TEST(test_to_upper_basic) {
  char *str = SAMPLE_STRING;
  char *expected = UPPER_SAMPLE;
  char *result = s21_to_upper(str);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_to_upper_empty) {
  char *str = EMPTY_STRING;
  char *expected = EMPTY_STRING;
  char *result = s21_to_upper(str);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_to_upper_fully_upper_case_str) {
  char *str = UPPER_SAMPLE;
  char *expected = UPPER_SAMPLE;
  char *result = s21_to_upper(str);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_to_upper_fully_lower_case_str) {
  char *str = LOWER_SAMPLE;
  char *expected = UPPER_SAMPLE;
  char *result = s21_to_upper(str);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_to_upper_non_letters_str) {
  char *str = SPECIAL_CHARS_STRING;
  char *expected = SPECIAL_CHARS_UPPER;
  char *result = s21_to_upper(str);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_to_upper_one_letter_str) {
  char *str = "a";
  char *expected = "A";
  char *result = s21_to_upper(str);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_to_upper_very_long_str) {
  char *str = malloc(LARGE_SIZE + 1);
  if (str == NULL) {
    ck_abort_msg("malloc failed");
  }
  memset(str, 'a', LARGE_SIZE);
  str[LARGE_SIZE] = '\0';
  char *expected = malloc(LARGE_SIZE + 1);
  if (expected == NULL) {
    ck_abort_msg("malloc failed");
  }
  memset(expected, 'A', LARGE_SIZE);
  expected[LARGE_SIZE] = '\0';
  char *result = s21_to_upper(str);
  ck_assert_str_eq(result, expected);
  free(str);
  free(expected);
  free(result);
}
END_TEST

// s21_to_lower
START_TEST(test_to_lower_basic) {
  char *str = SAMPLE_STRING;
  char *expected = LOWER_SAMPLE;
  char *result = s21_to_lower(str);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_to_lower_empty) {
  char *str = EMPTY_STRING;
  char *expected = EMPTY_STRING;
  char *result = s21_to_lower(str);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_to_lower_fully_lower_case_str) {
  char *str = LOWER_SAMPLE;
  char *expected = LOWER_SAMPLE;
  char *result = s21_to_lower(str);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_to_lower_fully_upper_case_str) {
  char *str = UPPER_SAMPLE;
  char *expected = LOWER_SAMPLE;
  char *result = s21_to_lower(str);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_to_lower_non_letters_str) {
  char *str = SPECIAL_CHARS_UPPER;
  char *expected = SPECIAL_CHARS_LOWER;
  char *result = s21_to_lower(str);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_to_lower_one_letter_str) {
  char *str = "A";
  char *expected = "a";
  char *result = s21_to_lower(str);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_to_lower_very_long_str) {
  char *str = malloc(LARGE_SIZE + 1);
  if (str == NULL) {
    ck_abort_msg("malloc failed");
  }
  memset(str, 'A', LARGE_SIZE);
  str[LARGE_SIZE] = '\0';
  char *expected = malloc(LARGE_SIZE + 1);
  if (expected == NULL) {
    ck_abort_msg("malloc failed");
  }
  memset(expected, 'a', LARGE_SIZE);
  expected[LARGE_SIZE] = '\0';
  char *result = s21_to_lower(str);
  ck_assert_str_eq(result, expected);
  free(str);
  free(expected);
  free(result);
}
END_TEST

// s21_insert
START_TEST(test_insert_basic) {
  char *src = SAMPLE_STRING;
  char *str = SAMPLE_STRING;
  size_t start_index = 0;
  char *expected = TWICE_SAMPLE;
  char *result = s21_insert(src, str, start_index);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_insert_middle) {
  char *src = "VERTER";
  char *str = "slayers";
  size_t start_index = 3;
  char *expected = "VERslayersTER";
  char *result = s21_insert(src, str, start_index);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_insert_end) {
  char *src = "VERTER";
  char *str = "slayers";
  size_t start_index = 6;
  char *expected = "VERTERslayers";
  char *result = s21_insert(src, str, start_index);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_insert_empty_src) {
  char *src = EMPTY_STRING;
  char *str = "slayers";
  size_t start_index = 0;
  char *expected = "slayers";
  char *result = s21_insert(src, str, start_index);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_insert_empty_str) {
  char *src = "VERTER";
  char *str = EMPTY_STRING;
  size_t start_index = 3;
  char *expected = "VERTER";
  char *result = s21_insert(src, str, start_index);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_insert_invalid_start_index) {
  char *src = "VERTER";
  char *str = "slayers";
  size_t start_index = 8;
  char *expected = NULL;
  char *result = s21_insert(src, str, start_index);
  ck_assert_ptr_eq(result, expected);
  if (result != NULL) {
    free(result);
  }
}
END_TEST

START_TEST(test_insert_very_long_str_and_src) {
  char *src = calloc(LARGE_SIZE / 2 + 1, sizeof(char));
  char *str = calloc(LARGE_SIZE / 2 + 1, sizeof(char));
  if (src == NULL || str == NULL) {
    ck_abort_msg("calloc failed");
  }
  memset(src, 'a', LARGE_SIZE / 2);
  memset(str, 'b', LARGE_SIZE / 2);
  size_t start_index = LARGE_SIZE / 4;
  char *result = s21_insert(src, str, start_index);
  ck_assert_ptr_ne(result, NULL);
  ck_assert_int_eq(strlen(result), LARGE_SIZE);
  free(src);
  free(str);
  free(result);
}
END_TEST

// s21_trim
START_TEST(test_trim_basic) {
  char *str = SAMPLE_STRING;
  char *trim_chars = SAMPLE_STRING;
  char *expected = EMPTY_STRING;
  char *result = s21_trim(str, trim_chars);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_trim_empty_str) {
  char *str = EMPTY_STRING;
  char *trim_chars = SAMPLE_STRING;
  char *expected = EMPTY_STRING;
  char *result = s21_trim(str, trim_chars);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_trim_empty_trim_chars) {
  char *str = SAMPLE_STRING;
  char *trim_chars = EMPTY_STRING;
  char *expected = SAMPLE_STRING;
  char *result = s21_trim(str, trim_chars);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_trim_no_chars_to_trim) {
  char *str = SAMPLE_STRING;
  char *trim_chars = NONE_IN_SAMPLE;
  char *expected = SAMPLE_STRING;
  char *result = s21_trim(str, trim_chars);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_trim_invalid_trim_chars) {
  char *str = SAMPLE_STRING;
  char *trim_chars = NULL;
  char *expected = NULL;
  char *result = s21_trim(str, trim_chars);
  ck_assert_ptr_eq(result, expected);
  if (result != NULL) {
    free(result);
  }
}
END_TEST

START_TEST(test_trim_very_long_strings) {
  char *str = calloc(LARGE_SIZE + 1, sizeof(char));
  char *trim_chars = calloc(LARGE_SIZE + 1, sizeof(char));
  if (str == NULL || trim_chars == NULL) {
    ck_abort_msg("calloc failed");
  }
  memset(str, '!', LARGE_SIZE);
  memset(trim_chars, '!', LARGE_SIZE);
  char *expected = EMPTY_STRING;
  char *result = s21_trim(str, trim_chars);
  ck_assert_str_eq(result, expected);
  free(str);
  free(trim_chars);
  free(result);
}
END_TEST

// sprintf
START_TEST(test_sprintf_c_basic) {
  char s21_str[STR_LEN] = {0};
  char std_str[STR_LEN] = {0};
  char format[] = "%c";
  char c = CHAR_TO_FIND;
  int s21_result = s21_sprintf(s21_str, format, c);
  int std_result = sprintf(std_str, format, c);
  ck_assert_int_eq(s21_result, std_result);
  ck_assert_str_eq(s21_str, std_str);
}
END_TEST

START_TEST(test_sprintf_d_basic) {
  char s21_str[STR_LEN] = {0};
  char std_str[STR_LEN] = {0};
  char format[] = "%d";
  int d = DEC;
  int s21_result = s21_sprintf(s21_str, format, d);
  int std_result = sprintf(std_str, format, d);
  ck_assert_int_eq(s21_result, std_result);
  ck_assert_str_eq(s21_str, std_str);
}
END_TEST

START_TEST(test_sprintf_f_basic) {
  char s21_str[STR_LEN] = {0};
  char std_str[STR_LEN] = {0};
  char format[] = "%f";
  double f = D_FLOAT;
  int s21_result = s21_sprintf(s21_str, format, f);
  int std_result = sprintf(std_str, format, f);
  ck_assert_int_eq(s21_result, std_result);
  ck_assert_str_eq(s21_str, std_str);
}
END_TEST

START_TEST(test_sprintf_s_basic) {
  const int len = strlen(SAMPLE_STRING) + 1;
  char s21_str[len];
  char std_str[len];
  memset(s21_str, 0, len);
  memset(std_str, 0, len);
  char format[] = "%s";
  char *s = SAMPLE_STRING;
  int s21_result = s21_sprintf(s21_str, format, s);
  int std_result = sprintf(std_str, format, s);
  ck_assert_int_eq(s21_result, std_result);
  ck_assert_str_eq(s21_str, std_str);
}
END_TEST

START_TEST(test_sprintf_u_basic) {
  char s21_str[STR_LEN] = {0};
  char std_str[STR_LEN] = {0};
  char format[] = "%u";
  unsigned int u = U_DEC;
  int s21_result = s21_sprintf(s21_str, format, u);
  int std_result = sprintf(std_str, format, u);
  ck_assert_int_eq(s21_result, std_result);
  ck_assert_str_eq(s21_str, std_str);
}
END_TEST

START_TEST(test_sprintf_percent_char_basic) {
  char s21_str[STR_LEN] = {0};
  char std_str[STR_LEN] = {0};
  char format[] = "%%";
  int s21_result = s21_sprintf(s21_str, format);
  int std_result = sprintf(std_str, format);
  ck_assert_int_eq(s21_result, std_result);
  ck_assert_str_eq(s21_str, std_str);
}
END_TEST

START_TEST(test_sprintf_g_G_basic) {
  char s21_str[STR_LEN] = {0};
  char std_str[STR_LEN] = {0};
  char format[] = "%g %G %g %G";
  double lf1 = PI;
  double lf2 = VERY_SMALL_VAL;
  int s21_result = s21_sprintf(s21_str, format, lf1, lf1, lf2, lf2);
  int std_result = sprintf(std_str, format, lf1, lf1, lf2, lf2);
  ck_assert_int_eq(s21_result, std_result);
  ck_assert_str_eq(s21_str, std_str);
}
END_TEST

START_TEST(test_sprintf_e_E_basic) {
  char s21_str[STR_LEN] = {0};
  char std_str[STR_LEN] = {0};
  char format[] = "%e %E";
  double f = D_FLOAT;
  int s21_result = s21_sprintf(s21_str, format, f, f);
  int std_result = sprintf(std_str, format, f, f);
  ck_assert_int_eq(s21_result, std_result);
  ck_assert_str_eq(s21_str, std_str);
}
END_TEST

START_TEST(test_sprintf_x_X_basic) {
  char s21_str[STR_LEN] = {0};
  char std_str[STR_LEN] = {0};
  char format[] = "%x %X";
  long int ld = LONG_INT;
  int s21_result = s21_sprintf(s21_str, format, ld, ld);
  int std_result = sprintf(std_str, format, ld, ld);
  ck_assert_int_eq(s21_result, std_result);
  ck_assert_str_eq(s21_str, std_str);
}
END_TEST

START_TEST(test_sprintf_o_basic) {
  char s21_str[STR_LEN] = {0};
  char std_str[STR_LEN] = {0};
  char format[] = "%o";
  long int ld = LONG_INT;
  int s21_result = s21_sprintf(s21_str, format, ld);
  int std_result = sprintf(std_str, format, ld);
  ck_assert_int_eq(s21_result, std_result);
  ck_assert_str_eq(s21_str, std_str);
}
END_TEST

START_TEST(test_sprintf_p_basic) {
  char s21_str[STR_LEN] = {0};
  char std_str[STR_LEN] = {0};
  char format[] = "%p";
  char c = CHAR_TO_FIND;
  int s21_result = s21_sprintf(s21_str, format, &c);
  int std_result = sprintf(std_str, format, &c);
  ck_assert_int_eq(s21_result, std_result);
  ck_assert_str_eq(s21_str, std_str);
}
END_TEST

START_TEST(test_sprintf_width_basic) {
  char s21_str[STR_LEN] = {0};
  char std_str[STR_LEN] = {0};
  char format[] = "%8d";
  int d = DEC;
  int s21_result = s21_sprintf(s21_str, format, d);
  int std_result = sprintf(std_str, format, d);
  ck_assert_int_eq(s21_result, std_result);
  ck_assert_str_eq(s21_str, std_str);
}
END_TEST

START_TEST(test_sprintf_width_left_justify) {
  char s21_str[STR_LEN] = {0};
  char std_str[STR_LEN] = {0};
  char format[] = "%-8d";
  int d = DEC;
  int s21_result = s21_sprintf(s21_str, format, d);
  int std_result = sprintf(std_str, format, d);
  ck_assert_int_eq(s21_result, std_result);
  ck_assert_str_eq(s21_str, std_str);
}
END_TEST

START_TEST(test_sprintf_width_zero_padding) {
  char s21_str[STR_LEN] = {0};
  char std_str[STR_LEN] = {0};
  char format[] = "%08d";
  int d = DEC;
  int s21_result = s21_sprintf(s21_str, format, d);
  int std_result = sprintf(std_str, format, d);
  ck_assert_int_eq(s21_result, std_result);
  ck_assert_str_eq(s21_str, std_str);
}
END_TEST

START_TEST(test_sprintf_width_star) {
  char s21_str[STR_LEN] = {0};
  char std_str[STR_LEN] = {0};
  char format[] = "%*d";
  int width = 8;
  int d = DEC;
  int s21_result = s21_sprintf(s21_str, format, width, d);
  int std_result = sprintf(std_str, format, width, d);
  ck_assert_int_eq(s21_result, std_result);
  ck_assert_str_eq(s21_str, std_str);
}
END_TEST

START_TEST(test_sprintf_forced_sign) {
  char s21_str[STR_LEN] = {0};
  char std_str[STR_LEN] = {0};
  char format[] = "%+d";
  unsigned int u = U_DEC;
  int s21_result = s21_sprintf(s21_str, format, u);
  int std_result = sprintf(std_str, format, u);
  ck_assert_int_eq(s21_result, std_result);
  ck_assert_str_eq(s21_str, std_str);
}
END_TEST

START_TEST(test_sprintf_space_for_positive) {
  char s21_str[STR_LEN] = {0};
  char std_str[STR_LEN] = {0};
  char format[] = "% d";
  unsigned int u = U_DEC;
  int s21_result = s21_sprintf(s21_str, format, u);
  int std_result = sprintf(std_str, format, u);
  ck_assert_int_eq(s21_result, std_result);
  ck_assert_str_eq(s21_str, std_str);
}
END_TEST

START_TEST(test_sprintf_hash_f_g_G_basic) {
  char s21_str[STR_LEN] = {0};
  char std_str[STR_LEN] = {0};
  char format[] = "%#.0f %#g %#G";
  float f = U_DEC;
  float g = D_FLOAT;
  int s21_result = s21_sprintf(s21_str, format, f, g, g);
  int std_result = sprintf(std_str, format, f, g, g);
  ck_assert_int_eq(s21_result, std_result);
  ck_assert_str_eq(s21_str, std_str);
}
END_TEST

START_TEST(test_sprintf_hash_o_x_X_basic) {
  char s21_str[STR_LEN] = {0};
  char std_str[STR_LEN] = {0};
  char format[] = "%#o %#x %#X";
  long int ld = LONG_INT;
  int s21_result = s21_sprintf(s21_str, format, ld, ld, ld);
  int std_result = sprintf(std_str, format, ld, ld, ld);
  ck_assert_int_eq(s21_result, std_result);
  ck_assert_str_eq(s21_str, std_str);
}
END_TEST

START_TEST(test_sprintf_precision_basic) {
  char s21_str[STR_LEN] = {0};
  char std_str[STR_LEN] = {0};
  char format[] = "%.8f";
  double lf = PI;
  int s21_result = s21_sprintf(s21_str, format, lf);
  int std_result = sprintf(std_str, format, lf);
  ck_assert_int_eq(s21_result, std_result);
  ck_assert_str_eq(s21_str, std_str);
}
END_TEST

START_TEST(test_sprintf_precision_zero) {
  char s21_str[STR_LEN] = {0};
  char std_str[STR_LEN] = {0};
  char format[] = "%.0f";
  double lf = PI;
  int s21_result = s21_sprintf(s21_str, format, lf);
  int std_result = sprintf(std_str, format, lf);
  ck_assert_int_eq(s21_result, std_result);
  ck_assert_str_eq(s21_str, std_str);
}
END_TEST

START_TEST(test_sprintf_precision_empty) {
  char s21_str[STR_LEN] = {0};
  char std_str[STR_LEN] = {0};
  char format[] = "%.f";
  double lf = D_FLOAT;
  int s21_result = s21_sprintf(s21_str, format, lf);
  int std_result = sprintf(std_str, format, lf);
  ck_assert_int_eq(s21_result, std_result);
  ck_assert_str_eq(s21_str, std_str);
}
END_TEST

START_TEST(test_sprintf_precision_star) {
  char s21_str[STR_LEN] = {0};
  char std_str[STR_LEN] = {0};
  char format[] = "%.*f";
  int precision = 8;
  double lf = PI;
  int s21_result = s21_sprintf(s21_str, format, precision, lf);
  int std_result = sprintf(std_str, format, precision, lf);
  ck_assert_int_eq(s21_result, std_result);
  ck_assert_str_eq(s21_str, std_str);
}
END_TEST

START_TEST(test_sprintf_precision_string) {
  char s21_str[STR_LEN] = {0};
  char std_str[STR_LEN] = {0};
  char format[] = "%.8s";
  char *s = SAMPLE_STRING;
  int s21_result = s21_sprintf(s21_str, format, s);
  int std_result = sprintf(std_str, format, s);
  ck_assert_int_eq(s21_result, std_result);
  ck_assert_str_eq(s21_str, std_str);
}
END_TEST

START_TEST(test_sprintf_length_h) {
  char s21_str[STR_LEN] = {0};
  char std_str[STR_LEN] = {0};
  char format[] = "%hd";
  short int hd = U_DEC;
  int s21_result = s21_sprintf(s21_str, format, hd);
  int std_result = sprintf(std_str, format, hd);
  ck_assert_int_eq(s21_result, std_result);
  ck_assert_str_eq(s21_str, std_str);
}
END_TEST

START_TEST(test_sprintf_length_l) {
  char s21_str[STR_LEN] = {0};
  char std_str[STR_LEN] = {0};
  char format[] = "%ld";
  long int ld = LONG_INT;
  int s21_result = s21_sprintf(s21_str, format, ld);
  int std_result = sprintf(std_str, format, ld);
  ck_assert_int_eq(s21_result, std_result);
  ck_assert_str_eq(s21_str, std_str);
}
END_TEST

START_TEST(test_sprintf_length_L) {
  char s21_str[STR_LEN] = {0};
  char std_str[STR_LEN] = {0};
  char format[] = "%Lf";
  long double lf = PI;
  int s21_result = s21_sprintf(s21_str, format, lf);
  int std_result = sprintf(std_str, format, lf);
  ck_assert_int_eq(s21_result, std_result);
  ck_assert_str_eq(s21_str, std_str);
}
END_TEST

START_TEST(test_sprintf_full_combination) {
  char s21_str[STR_LEN] = {0};
  char std_str[STR_LEN] = {0};
  char format[] = "%-+ 8.8Lf %-+ 8ld";
  long double lf = PI;
  long int ld = LONG_INT;
  int s21_result = s21_sprintf(s21_str, format, lf, ld);
  int std_result = sprintf(std_str, format, lf, ld);
  ck_assert_int_eq(s21_result, std_result);
  ck_assert_str_eq(s21_str, std_str);
}
END_TEST

// sscanf
START_TEST(test_sscanf_c_basic) {
  char s21_c;
  char std_c;
  char format[] = "%c";
  char str[] = "a";
  int s21_result = s21_sscanf(str, format, &s21_c);
  int std_result = sscanf(str, format, &std_c);
  ck_assert_int_eq(s21_result, std_result);
  ck_assert_int_eq(s21_c, std_c);
}
END_TEST

START_TEST(test_sscanf_d_basic) {
  int s21_d;
  int std_d;
  char format[] = "%d";
  char str[] = "8";
  int s21_result = s21_sscanf(str, format, &s21_d);
  int std_result = sscanf(str, format, &std_d);
  ck_assert_int_eq(s21_result, std_result);
  ck_assert_int_eq(s21_d, std_d);
}
END_TEST

START_TEST(test_sscanf_i_basic) {
  int s21_dec, s21_oct, s21_hex;
  int std_dec, std_oct, std_hex;
  char format[] = "%i %i %i";
  char str[] = "8 010 0x10";
  int s21_result = s21_sscanf(str, format, &s21_dec, &s21_oct, &s21_hex);
  int std_result = sscanf(str, format, &std_dec, &std_oct, &std_hex);
  ck_assert_int_eq(s21_result, std_result);
  ck_assert_int_eq(s21_dec, std_dec);
  ck_assert_int_eq(s21_oct, std_oct);
  ck_assert_int_eq(s21_hex, std_hex);
}
END_TEST

START_TEST(test_sscanf_f_basic) {
  float s21_f;
  float std_f;
  char format[] = "%f";
  char str[] = "3.14";
  int s21_result = s21_sscanf(str, format, &s21_f);
  int std_result = sscanf(str, format, &std_f);
  ck_assert_int_eq(s21_result, std_result);
  ck_assert_float_eq(s21_f, std_f);
}
END_TEST

START_TEST(test_sscanf_e_E_basic) {
  float s21_e, s21_E;
  float std_e, std_E;
  char format[] = "%e %E";
  char str[] = "3.14e-2 3.14E-2";
  int s21_result = s21_sscanf(str, format, &s21_e, &s21_E);
  int std_result = sscanf(str, format, &std_e, &std_E);
  ck_assert_int_eq(s21_result, std_result);
  ck_assert_float_eq(s21_e, std_e);
  ck_assert_float_eq(s21_E, std_E);
}
END_TEST

START_TEST(test_sscanf_g_G_basic) {
  float s21_g1, s21_g2, s21_G1, s21_G2;
  float std_g1, std_g2, std_G1, std_G2;
  char format[] = "%g %g %G %G";
  char str[] = "0.1 0.1 0.00001 0.00001";
  int s21_result = s21_sscanf(str, format, &s21_g1, &s21_g2, &s21_G1, &s21_G2);
  int std_result = sscanf(str, format, &std_g1, &std_g2, &std_G1, &std_G2);
  ck_assert_int_eq(s21_result, std_result);
  ck_assert_float_eq(s21_g1, std_g1);
  ck_assert_float_eq(s21_g2, std_g2);
  ck_assert_float_eq(s21_G1, std_G1);
  ck_assert_float_eq(s21_G2, std_G2);
}
END_TEST

START_TEST(test_sscanf_o_basic) {
  unsigned int s21_o;
  unsigned int std_o;
  char format[] = "%o";
  char str[] = "10";
  int s21_result = s21_sscanf(str, format, &s21_o);
  int std_result = sscanf(str, format, &std_o);
  ck_assert_int_eq(s21_result, std_result);
  ck_assert_int_eq(s21_o, std_o);
}
END_TEST

START_TEST(test_sscanf_u_basic) {
  unsigned int s21_u;
  unsigned int std_u;
  char format[] = "%u";
  char str[] = "8";
  int s21_result = s21_sscanf(str, format, &s21_u);
  int std_result = sscanf(str, format, &std_u);
  ck_assert_int_eq(s21_result, std_result);
  ck_assert_int_eq(s21_u, std_u);
}
END_TEST

START_TEST(test_sscanf_x_X_basic) {
  unsigned int s21_x1, s21_x2, s21_X1, s21_X2;
  unsigned int std_x1, std_x2, std_X1, std_X2;
  char format[] = "%x %X %x %X";
  char str[] = "0xf 0xF 0xF 0xf";
  int s21_result = s21_sscanf(str, format, &s21_x1, &s21_X1, &s21_x2, &s21_X2);
  int std_result = sscanf(str, format, &std_x1, &std_X1, &std_x2, &std_X2);
  ck_assert_int_eq(s21_result, std_result);
  ck_assert_int_eq(s21_x1, std_x1);
  ck_assert_int_eq(s21_x2, std_x2);
  ck_assert_int_eq(s21_X1, std_X1);
  ck_assert_int_eq(s21_X2, std_X2);
}
END_TEST

START_TEST(test_sscanf_s_basic) {
  char s21_str[STR_LEN] = {0};
  char std_str[STR_LEN] = {0};
  char format[] = "%s";
  char str[] = SAMPLE_STRING;
  int s21_result = s21_sscanf(str, format, s21_str);
  int std_result = sscanf(str, format, std_str);
  ck_assert_int_eq(s21_result, std_result);
  ck_assert_str_eq(s21_str, std_str);
}
END_TEST

START_TEST(test_sscanf_n_basic) {
  int s21_n = 0, std_n = 0;
  char format[] = "Chars before n%nChars after n";
  char str[] = "Chars before nChars after n";
  int s21_result = s21_sscanf(str, format, &s21_n);
  int std_result = sscanf(str, format, &std_n);
  ck_assert_int_ne(s21_n, 0);
  ck_assert_int_eq(s21_n, std_n);
}
END_TEST

START_TEST(test_sscanf_p_basic) {
  void *s21_p = NULL, *std_p = NULL;
  char format[] = "%p";
  char str[] = "0x1234abcd";
  int s21_result = s21_sscanf(str, format, &s21_p);
  int std_result = sscanf(str, format, &std_p);
  ck_assert_int_eq(s21_result, std_result);
  ck_assert_ptr_ne(s21_p, NULL);
  ck_assert_ptr_eq(s21_p, std_p);
}
END_TEST

START_TEST(test_sscanf_percent_char_basic) {
  int s21_i = 0, std_i = 0;
  char format[] = "%%%d";
  char str[] = "%8";
  int s21_result = s21_sscanf(str, format, &s21_i);
  int std_result = sscanf(str, format, &std_i);
  ck_assert_int_eq(s21_result, std_result);
  ck_assert_int_eq(s21_i, 8);
  ck_assert_int_eq(s21_i, std_i);
}
END_TEST

START_TEST(test_sscanf_width_float_basic) {
  float s21_f = 0, std_f = 0, ref_f = 1.0;
  char format[] = "%1f";
  char str[] = "1.1";
  int s21_result = s21_sscanf(str, format, &s21_f);
  int std_result = sscanf(str, format, &std_f);
  ck_assert_int_eq(s21_result, std_result);
  ck_assert_float_eq(s21_f, ref_f);
  ck_assert_float_eq(s21_f, std_f);
}
END_TEST

START_TEST(test_sscanf_width_chars_basic) {
  char s21_str[STR_LEN] = {0};
  char std_str[STR_LEN] = {0};
  char format[] = "%8c";
  char str[] = SAMPLE_STRING;
  int s21_result = s21_sscanf(str, format, s21_str);
  int std_result = sscanf(str, format, std_str);
  ck_assert_int_eq(s21_result, std_result);
  ck_assert_int_eq(strlen(s21_str), 8);
  ck_assert_str_eq(s21_str, std_str);
}
END_TEST

START_TEST(test_sscanf_skip_basic) {
  int s21_i = 0, std_i = 0, ref_i = 8;
  char format[] = "%*d %d";
  char str[] = "10 8";
  int s21_result = s21_sscanf(str, format, &s21_i);
  int std_result = sscanf(str, format, &std_i);
  ck_assert_int_eq(s21_result, std_result);
  ck_assert_int_eq(s21_i, ref_i);
  ck_assert_int_eq(s21_i, std_i);
}
END_TEST

START_TEST(test_sscanf_length_h_basic) {
  short int s21_hd = 0, std_hd = 0, ref_hd = 8;
  char format[] = "%hd";
  char str[] = "8";
  int s21_result = s21_sscanf(str, format, &s21_hd);
  int std_result = sscanf(str, format, &std_hd);
  ck_assert_int_eq(s21_result, std_result);
  ck_assert_int_eq(s21_hd, ref_hd);
  ck_assert_int_eq(s21_hd, std_hd);
}
END_TEST

START_TEST(test_sscanf_length_l_basic) {
  long int s21_ld = 0, std_ld = 0, ref_ld = LONG_INT;
  char format[] = "%ld";
  char str[] = "8888888888";
  int s21_result = s21_sscanf(str, format, &s21_ld);
  int std_result = sscanf(str, format, &std_ld);
  ck_assert_int_eq(s21_result, std_result);
  ck_assert_int_eq(s21_ld, ref_ld);
  ck_assert_int_eq(s21_ld, std_ld);
}
END_TEST

START_TEST(test_sscanf_length_L_basic) {
  long double s21_lf = 0, std_lf = 0, ref_lf = PI;
  char format[] = "%Lf";
  char str[] = "3.14159265359";
  int s21_result = s21_sscanf(str, format, &s21_lf);
  int std_result = sscanf(str, format, &std_lf);
  ck_assert_int_eq(s21_result, std_result);
  ck_assert_float_eq(s21_lf, ref_lf);
  ck_assert_float_eq(s21_lf, std_lf);
}
END_TEST

START_TEST(test_sscanf_invalid_d) {
  int s21_d = 0, std_d = 0;
  char format[] = "%d";
  char str[] = NONE_IN_SAMPLE;
  int s21_result = s21_sscanf(str, format, &s21_d);
  int std_result = sscanf(str, format, &std_d);
  ck_assert_int_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_sscanf_invalid_f) {
  float s21_f = 0, std_f = 0;
  char format[] = "%f";
  char str[] = NONE_IN_SAMPLE;
  int s21_result = s21_sscanf(str, format, &s21_f);
  int std_result = sscanf(str, format, &std_f);
  ck_assert_int_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_sscanf_unsigned_short_int) {
  unsigned short int s21_uhd = 0, std_uhd = 0, ref_uhd = 8;
  char format[] = "%hu";
  char str[] = "8";
  int s21_result = s21_sscanf(str, format, &s21_uhd);
  int std_result = sscanf(str, format, &std_uhd);
  ck_assert_int_eq(s21_result, std_result);
  ck_assert_int_eq(s21_uhd, ref_uhd);
  ck_assert_int_eq(s21_uhd, std_uhd);
}
END_TEST

START_TEST(test_sscanf_unsigned_long_int) {
  unsigned long int s21_ul = 0, std_ul = 0, ref_ul = LONG_INT;
  char format[] = "%lu";
  char str[] = "8888888888";
  int s21_result = s21_sscanf(str, format, &s21_ul);
  int std_result = sscanf(str, format, &std_ul);
  ck_assert_int_eq(s21_result, std_result);
  ck_assert_int_eq(s21_ul, ref_ul);
  ck_assert_int_eq(s21_ul, std_ul);
}
END_TEST

Suite *s21_string_plus_suite(void) {
  Suite *s;
  TCase *tc_memchr, *tc_memcmp, *tc_memcpy, *tc_memset, *tc_strncat, *tc_strchr,
      *tc_strncmp, *tc_strncpy, *tc_strcspn, *tc_strerror, *tc_strlen,
      *tc_strpbrk, *tc_strrchr, *tc_strstr, *tc_strtok, *tc_to_upper,
      *tc_to_lower, *tc_insert, *tc_trim, *tc_sprintf, *tc_sscanf;

  s = suite_create("s21_string_plus");

  tc_memchr = tcase_create("memchr");
  tcase_add_test(tc_memchr, test_memchr_found);
  tcase_add_test(tc_memchr, test_memchr_not_found);
  tcase_add_test(tc_memchr, test_memchr_empty_str);
  tcase_add_test(tc_memchr, test_memchr_zero_length);
  tcase_add_test(tc_memchr, test_memchr_out_of_set_length);
  tcase_add_test(tc_memchr, test_memchr_first_char);
  tcase_add_test(tc_memchr, test_memchr_last_char);
  tcase_add_test(tc_memchr, test_memchr_special_chars);
  tcase_add_test(tc_memchr, test_memchr_non_printable);
  tcase_add_test(tc_memchr, test_memchr_extended_ascii);
  tcase_add_test(tc_memchr, test_memchr_hex_bytes);
  suite_add_tcase(s, tc_memchr);

  tc_memcmp = tcase_create("memcmp");
  tcase_add_test(tc_memcmp, test_memcmp_equal);
  tcase_add_test(tc_memcmp, test_memcmp_different);
  tcase_add_test(tc_memcmp, test_memcmp_mid_length);
  tcase_add_test(tc_memcmp, test_memcmp_zero_length);
  tcase_add_test(tc_memcmp, test_memcmp_null_bytes);
  tcase_add_test(tc_memcmp, test_memcmp_extended_ascii);
  tcase_add_test(tc_memcmp, test_memcmp_large_data);
  suite_add_tcase(s, tc_memcmp);

  tc_memcpy = tcase_create("memcpy");
  tcase_add_test(tc_memcpy, test_memcpy_full);
  tcase_add_test(tc_memcpy, test_memcpy_partial);
  tcase_add_test(tc_memcpy, test_memcpy_zero);
  tcase_add_test(tc_memcpy, test_memcpy_one_byte);
  tcase_add_test(tc_memcpy, test_memcpy_str_with_null_term);
  tcase_add_test(tc_memcpy, test_memcpy_large_data);
  suite_add_tcase(s, tc_memcpy);

  tc_memset = tcase_create("memset");
  tcase_add_test(tc_memset, test_memset_full);
  tcase_add_test(tc_memset, test_memset_partial);
  tcase_add_test(tc_memset, test_memset_zero);
  tcase_add_test(tc_memset, test_memset_str_with_null_term);
  tcase_add_test(tc_memset, test_memset_extended_ascii_char);
  tcase_add_test(tc_memset, test_memset_very_large_data);
  suite_add_tcase(s, tc_memset);

  tc_strncat = tcase_create("strncat");
  tcase_add_test(tc_strncat, test_strncat_full);
  tcase_add_test(tc_strncat, test_strncat_partial);
  tcase_add_test(tc_strncat, test_strncat_zero);
  tcase_add_test(tc_strncat, test_strncat_out_of_range_n);
  tcase_add_test(tc_strncat, test_strncat_empty_src);
  tcase_add_test(tc_strncat, test_strncat_src_with_null_term);
  tcase_add_test(tc_strncat, test_strncat_very_large_src);
  suite_add_tcase(s, tc_strncat);

  tc_strchr = tcase_create("strchr");
  tcase_add_test(tc_strchr, test_strchr_found);
  tcase_add_test(tc_strchr, test_strchr_not_found);
  tcase_add_test(tc_strchr, test_strchr_searching_null_term);
  tcase_add_test(tc_strchr, test_strchr_empty_str);
  tcase_add_test(tc_strchr, test_strchr_extended_ascii);
  suite_add_tcase(s, tc_strchr);

  tc_strncmp = tcase_create("strncmp");
  tcase_add_test(tc_strncmp, test_strncmp_equal);
  tcase_add_test(tc_strncmp, test_strncmp_different);
  tcase_add_test(tc_strncmp, test_strncmp_zero_length);
  tcase_add_test(tc_strncmp, test_strncmp_mid_range_length);
  tcase_add_test(tc_strncmp, test_strncmp_out_of_range_length);
  tcase_add_test(tc_strncmp, test_strncmp_empty_str);
  tcase_add_test(tc_strncmp, test_strncmp_str_with_null_term);
  tcase_add_test(tc_strncmp, test_strncmp_extended_ascii);
  suite_add_tcase(s, tc_strncmp);

  tc_strncpy = tcase_create("strncpy");
  tcase_add_test(tc_strncpy, test_strncpy_full);
  tcase_add_test(tc_strncpy, test_strncpy_partial);
  tcase_add_test(tc_strncpy, test_strncpy_zero);
  tcase_add_test(tc_strncpy, test_strncpy_src_shorter_then_n);
  tcase_add_test(tc_strncpy, test_strncpy_src_longer_then_n);
  tcase_add_test(tc_strncpy, test_strncpy_src_with_null_term);
  tcase_add_test(tc_strncpy, test_strncpy_src_with_non_printable);
  tcase_add_test(tc_strncpy, test_strncpy_src_with_extended_ascii);
  tcase_add_test(tc_strncpy, test_strncpy_very_large_data);
  suite_add_tcase(s, tc_strncpy);

  tc_strcspn = tcase_create("strcspn");
  tcase_add_test(tc_strcspn, test_strcspn_found);
  tcase_add_test(tc_strcspn, test_strcspn_not_found);
  tcase_add_test(tc_strcspn, test_strcspn_empty_str1);
  tcase_add_test(tc_strcspn, test_strcspn_empty_str2);
  tcase_add_test(tc_strcspn, test_strcspn_empty_both);
  tcase_add_test(tc_strcspn, test_strcspn_multiple_occurances);
  tcase_add_test(tc_strcspn, test_strcspn_special_chars);
  tcase_add_test(tc_strcspn, test_strcspn_non_printable_str1);
  tcase_add_test(tc_strcspn, test_strcspn_non_printable_str2);
  suite_add_tcase(s, tc_strcspn);

  tc_strerror = tcase_create("strerror");
  tcase_add_test(tc_strerror, test_strerror_basic);
  tcase_add_test(tc_strerror, test_strerror_negative);
  tcase_add_test(tc_strerror, test_strerror_large_positive);
  suite_add_tcase(s, tc_strerror);

  tc_strlen = tcase_create("strlen");
  tcase_add_test(tc_strlen, test_strlen_basic);
  tcase_add_test(tc_strlen, test_strlen_empty);
  tcase_add_test(tc_strlen, test_strlen_str_with_null_term);
  tcase_add_test(tc_strlen, test_strlen_extended_ascii);
  tcase_add_test(tc_strlen, test_strlen_very_long_str);
  tcase_add_test(tc_strlen, test_strlen_multiple_null_terms);
  suite_add_tcase(s, tc_strlen);

  tc_strpbrk = tcase_create("strpbrk");
  tcase_add_test(tc_strpbrk, test_strpbrk_found);
  tcase_add_test(tc_strpbrk, test_strpbrk_not_found);
  tcase_add_test(tc_strpbrk, test_strpbrk_multiple_occurances);
  tcase_add_test(tc_strpbrk, test_strpbrk_empty_str1);
  tcase_add_test(tc_strpbrk, test_strpbrk_empty_str2);
  tcase_add_test(tc_strpbrk, test_strpbrk_empty_both);
  tcase_add_test(tc_strpbrk, test_strpbrk_special_chars);
  tcase_add_test(tc_strpbrk, test_strpbrk_non_printable);
  suite_add_tcase(s, tc_strpbrk);

  tc_strrchr = tcase_create("strrchr");
  tcase_add_test(tc_strrchr, test_strrchr_found);
  tcase_add_test(tc_strrchr, test_strrchr_not_found);
  tcase_add_test(tc_strrchr, test_strrchr_searching_null_term);
  tcase_add_test(tc_strrchr, test_strrchr_empty_str);
  tcase_add_test(tc_strrchr, test_strrchr_extended_ascii);
  suite_add_tcase(s, tc_strrchr);

  tc_strstr = tcase_create("strstr");
  tcase_add_test(tc_strstr, test_strstr_found_basic);
  tcase_add_test(tc_strstr, test_strstr_not_found_basic);
  tcase_add_test(tc_strstr, test_strstr_found_at_start);
  tcase_add_test(tc_strstr, test_strstr_found_at_end);
  tcase_add_test(tc_strstr, test_strstr_empty_haystack);
  tcase_add_test(tc_strstr, test_strstr_empty_needle);
  tcase_add_test(tc_strstr, test_strstr_multiple_occurrences);
  tcase_add_test(tc_strstr, test_strstr_extended_ascii);
  suite_add_tcase(s, tc_strstr);

  tc_strtok = tcase_create("strtok");
  tcase_add_test(tc_strtok, test_strtok_existing_delim);
  tcase_add_test(tc_strtok, test_strtok_non_existing_delim);
  tcase_add_test(tc_strtok, test_strtok_empty_string);
  tcase_add_test(tc_strtok, test_strtok_empty_delim);
  tcase_add_test(tc_strtok, test_strtok_consecutive_delim);
  tcase_add_test(tc_strtok, test_strtok_leading_delim);
  tcase_add_test(tc_strtok, test_strtok_trailing_delim);
  tcase_add_test(tc_strtok, test_strtok_mixed_delims);
  tcase_add_test(tc_strtok, test_strtok_only_delims_in_str);
  suite_add_tcase(s, tc_strtok);

  tc_to_upper = tcase_create("to_upper");
  tcase_add_test(tc_to_upper, test_to_upper_basic);
  tcase_add_test(tc_to_upper, test_to_upper_empty);
  tcase_add_test(tc_to_upper, test_to_upper_fully_upper_case_str);
  tcase_add_test(tc_to_upper, test_to_upper_fully_lower_case_str);
  tcase_add_test(tc_to_upper, test_to_upper_non_letters_str);
  tcase_add_test(tc_to_upper, test_to_upper_one_letter_str);
  tcase_add_test(tc_to_upper, test_to_upper_very_long_str);
  suite_add_tcase(s, tc_to_upper);

  tc_to_lower = tcase_create("to_lower");
  tcase_add_test(tc_to_lower, test_to_lower_basic);
  tcase_add_test(tc_to_lower, test_to_lower_empty);
  tcase_add_test(tc_to_lower, test_to_lower_fully_upper_case_str);
  tcase_add_test(tc_to_lower, test_to_lower_fully_lower_case_str);
  tcase_add_test(tc_to_lower, test_to_lower_non_letters_str);
  tcase_add_test(tc_to_lower, test_to_lower_one_letter_str);
  tcase_add_test(tc_to_lower, test_to_lower_very_long_str);
  suite_add_tcase(s, tc_to_lower);

  tc_insert = tcase_create("insert");
  tcase_add_test(tc_insert, test_insert_basic);
  tcase_add_test(tc_insert, test_insert_middle);
  tcase_add_test(tc_insert, test_insert_end);
  tcase_add_test(tc_insert, test_insert_empty_str);
  tcase_add_test(tc_insert, test_insert_empty_src);
  tcase_add_test(tc_insert, test_insert_invalid_start_index);
  tcase_add_test(tc_insert, test_insert_very_long_str_and_src);
  suite_add_tcase(s, tc_insert);

  tc_trim = tcase_create("trim");
  tcase_add_test(tc_trim, test_trim_basic);
  tcase_add_test(tc_trim, test_trim_empty_str);
  tcase_add_test(tc_trim, test_trim_empty_trim_chars);
  tcase_add_test(tc_trim, test_trim_no_chars_to_trim);
  tcase_add_test(tc_trim, test_trim_invalid_trim_chars);
  tcase_add_test(tc_trim, test_trim_very_long_strings);
  suite_add_tcase(s, tc_trim);

  tc_sprintf = tcase_create("sprintf");
  tcase_add_test(tc_sprintf, test_sprintf_c_basic);
  tcase_add_test(tc_sprintf, test_sprintf_d_basic);
  tcase_add_test(tc_sprintf, test_sprintf_f_basic);
  tcase_add_test(tc_sprintf, test_sprintf_s_basic);
  tcase_add_test(tc_sprintf, test_sprintf_u_basic);
  tcase_add_test(tc_sprintf, test_sprintf_percent_char_basic);
  tcase_add_test(tc_sprintf, test_sprintf_g_G_basic);
  tcase_add_test(tc_sprintf, test_sprintf_e_E_basic);
  tcase_add_test(tc_sprintf, test_sprintf_x_X_basic);
  tcase_add_test(tc_sprintf, test_sprintf_o_basic);
  tcase_add_test(tc_sprintf, test_sprintf_p_basic);
  tcase_add_test(tc_sprintf, test_sprintf_width_basic);
  tcase_add_test(tc_sprintf, test_sprintf_width_left_justify);
  tcase_add_test(tc_sprintf, test_sprintf_width_zero_padding);
  tcase_add_test(tc_sprintf, test_sprintf_width_star);
  tcase_add_test(tc_sprintf, test_sprintf_forced_sign);
  tcase_add_test(tc_sprintf, test_sprintf_space_for_positive);
  tcase_add_test(tc_sprintf, test_sprintf_hash_f_g_G_basic);
  tcase_add_test(tc_sprintf, test_sprintf_hash_o_x_X_basic);
  tcase_add_test(tc_sprintf, test_sprintf_precision_basic);
  tcase_add_test(tc_sprintf, test_sprintf_precision_zero);
  tcase_add_test(tc_sprintf, test_sprintf_precision_empty);
  tcase_add_test(tc_sprintf, test_sprintf_precision_star);
  tcase_add_test(tc_sprintf, test_sprintf_precision_string);
  tcase_add_test(tc_sprintf, test_sprintf_length_h);
  tcase_add_test(tc_sprintf, test_sprintf_length_l);
  tcase_add_test(tc_sprintf, test_sprintf_length_L);
  tcase_add_test(tc_sprintf, test_sprintf_full_combination);
  suite_add_tcase(s, tc_sprintf);

  tc_sscanf = tcase_create("sscanf");
  tcase_add_test(tc_sscanf, test_sscanf_c_basic);
  tcase_add_test(tc_sscanf, test_sscanf_d_basic);
  tcase_add_test(tc_sscanf, test_sscanf_i_basic);
  tcase_add_test(tc_sscanf, test_sscanf_f_basic);
  tcase_add_test(tc_sscanf, test_sscanf_e_E_basic);
  tcase_add_test(tc_sscanf, test_sscanf_g_G_basic);
  tcase_add_test(tc_sscanf, test_sscanf_o_basic);
  tcase_add_test(tc_sscanf, test_sscanf_u_basic);
  tcase_add_test(tc_sscanf, test_sscanf_x_X_basic);
  tcase_add_test(tc_sscanf, test_sscanf_s_basic);
  tcase_add_test(tc_sscanf, test_sscanf_n_basic);
  tcase_add_test(tc_sscanf, test_sscanf_p_basic);
  tcase_add_test(tc_sscanf, test_sscanf_percent_char_basic);
  tcase_add_test(tc_sscanf, test_sscanf_width_float_basic);
  tcase_add_test(tc_sscanf, test_sscanf_width_chars_basic);
  tcase_add_test(tc_sscanf, test_sscanf_skip_basic);
  tcase_add_test(tc_sscanf, test_sscanf_length_h_basic);
  tcase_add_test(tc_sscanf, test_sscanf_length_l_basic);
  tcase_add_test(tc_sscanf, test_sscanf_length_L_basic);
  tcase_add_test(tc_sscanf, test_sscanf_invalid_d);
  tcase_add_test(tc_sscanf, test_sscanf_invalid_f);
  tcase_add_test(tc_sscanf, test_sscanf_unsigned_short_int);
  tcase_add_test(tc_sscanf, test_sscanf_unsigned_long_int);
  suite_add_tcase(s, tc_sscanf);

  return s;
}

int main() {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = s21_string_plus_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

void run_strtok_tests(char *str, char *delim) {
  const size_t len = strlen(str);
  char *std_ptr = NULL, *s21_ptr = NULL, buf[len];
  strncpy(buf, str, len);
  buf[len] = '\0';
  ck_assert_str_eq(str, buf);

  std_ptr = strtok(str, delim);
  s21_ptr = s21_strtok(buf, delim);

  while (std_ptr && s21_ptr) {
    ck_assert_str_eq(std_ptr, s21_ptr);
    std_ptr = strtok(NULL, delim);
    s21_ptr = s21_strtok(NULL, delim);
  }
  ck_assert_ptr_eq(s21_ptr, std_ptr);
}
