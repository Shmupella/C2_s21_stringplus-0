SOURSES=\
	insert.c\
	memchr.c\
	memcmp.c\
	memcpy.c\
	memmove.c\
	memset.c\
	strcat.c\
	strchr.c\
	strcmp.c\
	strcpy.c\
	strcspn.c\
	strerror.c\
	strlen.c\
	strncat.c\
	strncmp.c\
	strncpy.c\
	strpbrk.c\
	strrchr.c\
	strspn.c\
	strstr.c\
	strtok.c\
	to_lower.c\
	to_upper.c\
	trim.c\
	sprintf.c

OBJECTS = $(addprefix ./build/string/, $(patsubst %.c,%.o, $(SOURSES)))

TEST_SOURCES=$(shell find tests/ -name '*.c')
TEST_OBJECTS=$(addprefix ./build/, $(patsubst %.c,%.o, $(TEST_SOURCES)))
DEBUG_FLAG=
ERROR_FLAG=
GCOVFLAGS= -fprofile-arcs -ftest-coverage

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
        CCHECK = -pthread -lcheck_pic -pthread -lrt -lm -lsubunit
    endif
ifeq ($(UNAME_S),Darwin)
        CCHECK = -lcheck 
endif

all: clean s21_string.a test

./build/string/%.o: %.c
	gcc -MD -c $< -lm -o $@ $(ERROR_FLAG) $(DEBUG_FLAG)

./build/tests/%.o: ./tests/%.c
	gcc -MD -c $< -o $@ $(ERROR_FLAG)

s21_string.a: $(OBJECTS)
	ar rcs s21_string.a $^
	ranlib s21_string.a

test: $(TEST_OBJECTS) s21_string.a
	gcc $(TEST_OBJECTS) -L. s21_string.a -o tests.out $(CCHECK) $(DEBUG_FLAG)


gcov_report: s21_string.a
	gcc $(GCOVFLAGS) ./tests/*Case.c ./tests/tests.c $(SOURSES) $(CHECKFLAGS) -o gcovreport $(CCHECK)
	./gcovreport
	lcov -t "GcovReport" -o gcovreport.info -c -d .
	genhtml -o report gcovreport.info

clean:
	find . -name "*.o" -type f -delete
	find . -name "*.d" -type f -delete
	find . -name "*.a" -type f -delete
	find . -name "*.out" -type f -delete
	find . -name "*.gcno" -type f -delete
	find . -name "*.gcda" -type f -delete
	rm -rf ./main
	rm -rf tests.out
	rm -rf report
	rm -rf gcovreport.info
	rm -rf gcovreport

.PHONY: clean fprog check

check:
	cp ../materials/linters/CPPLINT.cfg .
	python3 ../materials/linters/cpplint.py *.c *.h ./tests/*.h ./tests/*.c
	rm -rf CPPLINT.cfg

main: s21_string.a main.c
	gcc main.c -L. s21_string.a -lm -o main $(DEBUG_FLAG)

fprog: main
	./main