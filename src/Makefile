.PHONY: all clean test s21_string.a check rebuild open gcov_report
CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c11
LINUX=-lsubunit -lrt -lpthread -lm
LIBS=-lcheck
LFLAGS=-fprofile-arcs -ftest-coverage
OS=$(shell uname -s)

all: clean s21_string.a test

s21_string.a: s21_string.o
	ar rcs s21_string.a s21_string.o
	cp s21_string.a libs21_string.a
	cp s21_string.a ls21_string.a
	ranlib libs21_string.a
	ranlib ls21_string.a

s21_string.o: s21_string.c
	$(CC) -c s21_string.c -o s21_string.o

test: s21_string.a
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) test.c s21_string.a -o test.out $(LIBS)
	./test.out; exit 0
else
	$(CC) $(CFLAGS) test.c s21_string.a -o test.out $(LIBS) $(LINUX)
	./test.out; exit 0
endif

gcov_report:
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) $(LFLAGS) test.c s21_string.c -o test.out $(LIBS)
else
	$(CC) $(CFLAGS) $(LFLAGS) test.c s21_string.c -o test.out $(LIBS) $(LINUX)
endif
	./test.out
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info

open:
	open report/index.html

rebuild: clean all

check:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./test.out
else
	valgrind ./test.out --leak-check=full
endif
	make clean

clean:
	rm -rf *.gc* *.o *.a *.out *.info test.out
	rm -rf report
