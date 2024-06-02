.PHONY: all s21_matrix_oop.a test gcov_report check rebuild clean test.o leak
CC = g++
CFLAGS = -Wall -Werror -Wextra -std=c++17
GCOVFLAGS =  -fprofile-arcs -ftest-coverage 
LC = lcov -c -d .
C_FILES = s21_matrix_oop.cc
O_FILES = s21*.o
LIBS=-lcheck
LINUX=-lcheck -lm -lpthread -lrt -lsubunit
LDLIBS = -lgtest -lgtest_main
OS=$(shell uname -s)

all : s21_matrix_oop.a
clean : 
	rm -rf *.o *.gcno *.gcda *.info test.out s21_matrix_oop.a ./report
	rm -rf *.dSYM *.gch
	rm -rf test gcov_test gcov_report/

rebuild : clean all

$(O_FILES) :
	$(CC) $(CFLAGS) -c $(C_FILES) s21_matrix_oop.h
test.o :
	$(CC) $(CFLAGS) -c -lgtest -pthread test.cc
s21_matrix_oop.a :
	$(CC) $(CFLAGS) -c $(C_FILES)
	ar r s21_matrix_oop.a $(O_FILES)

test: clean all
	$(CC) $(FLAGS) unit_tests.cc s21_matrix_oop.a -lgtest -pthread -o test
	./test

leak: test
ifeq ($(OS), Darwin)
	leaks -atExit -- ./test
else 
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./test
endif

gcov_report: all
ifeq ($(OS), Darwin)
	$(CC) $(GCOVFLAGS) unit_tests.cc $(C_FILES) -o report.out $(LIBS) $(LDLIBS)
else
	$(CC) $(GCOVFLAGS) unit_tests.cc $(C_FILES) -o report.out $(LINUX) $(LDLIBS)
endif
	./report.out
	lcov -t "gcov_report" -o report.info --no-external -c -d .
	genhtml -o report/ report.info
	rm -f *.gcno *.gcda *.info report.out *.gcov *.o
	open ./report/index.html


check:
	cp ../materials/linters/.clang-format ./
	clang-format -i *.cc *.h
	clang-format -n *.cc *.h
	rm -rf .clang-format