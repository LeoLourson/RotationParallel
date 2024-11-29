CC = gcc 
CFLAGS = -W -Wall -Wfloat-equal -Wpointer-arith -Wwrite-strings -Wcast-align -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wno-long-long -Wcast-align -Winline -Werror -pedantic -pedantic-errors -Wunused -Wuninitialized --param inline-unit-growth=1000000 --param max-inline-insns-single=10000000 --param large-function-growth=10000000 -fPIC -lpthread -g
m.e: main.o functions.o solution.o head.h MyException.h
	g++ main.o functions.o solution.o -o m.e -lm
main.o: main.cpp head.h MyException.h
	g++ main.cpp $(CFLAGS) -c
functions.o: functions.cpp head.h MyException.h
	g++ functions.cpp $(CFLAGS) -c
solution.o: solution.cpp head.h MyException.h
	g++ solution.cpp $(CFLAGS) -c
clean:
	rm -f m.e main.o functions.o solution.o
