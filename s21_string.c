#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  const unsigned char *p = str;
  if (*p) {
    while (1) {
      if (!n || *p == c) break;
      n--;
      p++;
    }
  }
  if (!n) p = S21_NULL;
  return ((void *)p);
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const unsigned char *byte1 = (const unsigned char *)str1;
  const unsigned char *byte2 = (const unsigned char *)str2;
  int diff = 0;
  for (s21_size_t i = 0; i < n; i++) {
    if (byte1[i] != byte2[i]) {
      diff = byte1[i] - byte2[i];
      break;
    }
  }
  return diff;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  unsigned char *tmp_dest = (unsigned char *)dest;
  const unsigned char *tmp_src = (const unsigned char *)src;
  for (s21_size_t i = 0; i < n; i++) {
    tmp_dest[i] = tmp_src[i];
  }
  return dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *tmp_src = (unsigned char *)str;
  for (s21_size_t i = 0; i < n; i++) {
    tmp_src[i] = c;
  }
  return str;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *ptr = dest + s21_strlen(dest);
  s21_strncpy(ptr, src, n);
  *(ptr + n) = '\0';
  return dest;
}

char *s21_strchr(const char *str, int c) {
  int found = 0;
  const char *result = S21_NULL;

  while (*str && !found) {
    if (*str == c) {
      found = 1;
      result = str;
    }
    ++str;
  }

  if (!found && c == '\0') {
    result = str;
  }

  return (char *)result;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  while (n && *str1 && *str2 && (*str1 == *str2)) {
    str1++;
    str2++;
    n--;
  }
  return (n == 0) ? 0 : ((unsigned char)*str1 - (unsigned char)*str2);
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t i;
  for (i = 0; i < n && src[i] != '\0'; i++) dest[i] = src[i];
  for (; i < n; i++) dest[i] = '\0';
  return dest;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  unsigned char ascii[ASCII_L];
  for (int i = 0; i < ASCII_L; i++) *(ascii + i) = 0;
  for (int i = 0; *(str2 + i); i++) ascii[(int)*(str2 + i)]++;

  s21_size_t byte = 0;
  while (1) {
    if (!(*(str1 + byte)) || ascii[(int)*(str1 + byte)] > 0) break;
    byte++;
  }
  return (byte);
}

char *s21_strerror(int errnum) {
  char *error_list[] = ERROR_NAMES;
  static char error[MAX_LEN_ERROR];
  s21_sprintf(error, "%s %d",
              (OS) ? "Unknown error" : "Unknown error:", errnum);
  return (OS) ? ((errnum >= 0 && errnum <= 133) ? (char *)error_list[errnum]
                                                : error)
              : ((errnum >= 0 && errnum <= 106) ? (char *)error_list[errnum]
                                                : error);
}

s21_size_t s21_strlen(const char *str) {
  s21_size_t len = 0;
  for (; str[len]; len++);
  return len;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  char ascii[ASCII_L];
  const char *p;
  for (int i = 0; i < ASCII_L; i++) *(ascii + i) = 0;
  for (int i = 0; *(str2 + i); i++) ascii[(int)*(str2 + i)]++;
  for (p = str1;; p++)
    if (!(*p) || ascii[(int)*p] > 0) break;
  if (!(*p)) p = S21_NULL;
  return ((char *)p);
}

char *s21_strrchr(const char *str, int c) {
  const char *result = S21_NULL;

  while (*str) {
    if (*str == c) {
      result = str;
    }
    ++str;
  }

  if (c == '\0') {
    result = str;
  }

  return (char *)result;
}

char *s21_strstr(const char *haystack, const char *needle) {
  s21_size_t n = s21_strlen(haystack);
  s21_size_t m = s21_strlen(needle);
  char *result = S21_NULL;
  if (m == 0) {
    result = (char *)haystack;
  } else {
    int prefix[m];
    int len = 0;
    prefix[0] = 0;
    for (s21_size_t i = 1; i < m; i++) {
      while (len > 0 && needle[i] != needle[len]) len = needle[len - 1];
      if (needle[i] == needle[len]) len++;
      prefix[i] = len;
    }
    s21_size_t j = 0;
    for (s21_size_t i = 0; i < n; i++) {
      while (j > 0 && haystack[i] != needle[j]) j = prefix[j - 1];
      if (haystack[i] == needle[j]) j++;
      if (j == m) {
        result = (char *)(haystack + i - m + 1);
        break;
      }
    }
  }
  return result;
}

char *s21_strtok(char *str, const char *delim) {
  static char *next_token = S21_NULL;
  char *result = S21_NULL;

  if (str == S21_NULL) str = next_token;

  next_token = S21_NULL;

  if (str != S21_NULL) {
    while (*str != '\0' && is_delim(*str, delim)) {
      str++;
    }
    if (*str != '\0') {
      result = str;
      while (*str != '\0' && !is_delim(*str, delim)) {
        str++;
      }
      if (*str != '\0') {
        *str = '\0';
        next_token = str + 1;
      }
    }
  }
  return result;
}

int is_delim(char ch, const char *delim) {
  int flag_delim = 0;
  for (const char *d = delim; *d != '\0' && !flag_delim; d++) {
    if (ch == *d) flag_delim = 1;
  }
  return flag_delim;
}

void *s21_to_upper(const char *str) {
  s21_size_t len = s21_strlen(str);
  char *upper_str = malloc(len + 1);

  if (str == S21_NULL || upper_str == S21_NULL) return S21_NULL;

  for (s21_size_t i = 0; i < len; ++i) {
    if (str[i] >= 'a' && str[i] <= 'z') {
      upper_str[i] = str[i] - ('a' - 'A');
    } else {
      upper_str[i] = str[i];
    }
  }
  upper_str[len] = '\0';

  return upper_str;
}

void *s21_to_lower(const char *str) {
  s21_size_t len = s21_strlen(str);
  char *lower_str = malloc(len + 1);

  if (str == S21_NULL || lower_str == S21_NULL) return S21_NULL;

  for (s21_size_t i = 0; i < len; ++i) {
    if (str[i] >= 'A' && str[i] <= 'Z') {
      lower_str[i] = str[i] + ('a' - 'A');
    } else {
      lower_str[i] = str[i];
    }
  }
  lower_str[len] = '\0';

  return lower_str;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  if (src == S21_NULL || str == S21_NULL || start_index > s21_strlen(src)) {
    return S21_NULL;
  }

  s21_size_t src_len = s21_strlen(src);
  s21_size_t str_len = s21_strlen(str);
  s21_size_t total_len = src_len + str_len + 1;

  char *result = S21_NULL;
  int bad_insert = 0;

  result = (char *)malloc(total_len);
  if (result == S21_NULL) {
    bad_insert = 1;
  }

  if (!bad_insert) {
    s21_strncpy(result, src, start_index);
    result[start_index] = '\0';
    s21_strncat(result, str, str_len);
    s21_strncat(result, src + start_index, src_len - start_index);
  }

  return result;
}

void *s21_trim(const char *src, const char *trim_chars) {
  if (src == S21_NULL || trim_chars == S21_NULL) return S21_NULL;

  s21_size_t len = s21_strlen(src);
  s21_size_t start = 0;
  s21_size_t end;

  if (len == 0) {
    end = 0;
  } else {
    end = len - 1;
  }

  while (start <= end && s21_strchr(trim_chars, src[start]) != S21_NULL)
    ++start;

  while (end >= start && s21_strchr(trim_chars, src[end]) != S21_NULL) --end;

  char *result = S21_NULL;
  int bad_trim = 0;
  if (start > end) {
    bad_trim = 1;
    result = malloc(1);
    if (result) result[0] = '\0';
  }
  if (!bad_trim) {
    s21_size_t new_len = end - start + 1;
    result = malloc(new_len + 1);
    s21_memcpy(result, &src[start], new_len);
    result[new_len] = '\0';
  }

  return result;
}