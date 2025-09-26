TEST = all_tests
CC = gcc
CFlags = -Wall -Wextra -Werror -std=c11
TESTS_FLAGS = -lcheck -Wno-format-security
TESTS_EXEC = s21_string_test
TESTS_SRC = test_s21_string.c s21_string.c s21_sscanf.c s21_sprintf.c
OS := $(shell uname -s)

ifeq ($(OS), Darwin)
	TESTS_FLAGS +=
else
	TESTS_FLAGS += -lm -lsubunit
endif

all: gcov_report

gcov_report:
	$(MAKE) clean
	COVERAGE=1 $(MAKE) test
	lcov -t "$(TEST)" -o $(TEST).info -c -d .
	genhtml -o report $(TEST).info

test: s21_string.a test_s21_string.o
	$(CC) -o $(TESTS_EXEC) test_s21_string.o s21_string.a $(TESTS_FLAGS) $(if $(COVERAGE),--coverage,)
	./$(TESTS_EXEC)

test_s21_string.o: test_s21_string.c
	$(CC) -c $(TESTS_FLAGS) $(if $(COVERAGE),--coverage,) test_s21_string.c

s21_string.a: s21_sprintf.o s21_string.o s21_sscanf.o
	ar crs s21_string.a s21_sprintf.o s21_string.o s21_sscanf.o
	ranlib s21_string.a

s21_sprintf.o: s21_sprintf.c s21_sprintf.h
	$(CC) -c $(CFlags) $(if $(COVERAGE),--coverage,) s21_sprintf.c

s21_string.o: s21_string.c s21_string.h
	$(CC) -c $(CFlags) $(if $(COVERAGE),--coverage,) s21_string.c

s21_sscanf.o: s21_sscanf.c s21_sscanf.h
	$(CC) -c $(CFlags) $(if $(COVERAGE),--coverage,) s21_sscanf.c

clean:
	rm -f *.o *.a *.gcda *.gcno *.info
	rm -f $(TESTS_EXEC)
	rm -rf report

.PHONY: all test clean gcov_report