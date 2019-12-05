#  $@ Имя цели обрабатываемого правила
#  $< Имя первой зависимости обрабатываемого правила
#  $^ Список всех зависимостей обрабатываемого правила

# компилятор
CC = gcc
# флаги которые передаются компилятору
CFLAGS = -Wall -I.

DEPS = findmax.h findmax_test.h

all: findmax_test

findmax.o: findmax.c $(DEPS)
	$(CC) $(CFLAGS) -c findmax.c

findmax_test.o: findmax_test.c $(DEPS)
	$(CC) $(CFLAGS) -c findmax_test.c

main.o: main.c $(DEPS)
	$(CC) $(CFLAGS) -c main.c

findmax_test: main.o findmax.o findmax_test.o
	$(CC) $(CFLAGS) -o $@ $^


clean:
	rm -rf *.o findmax_test
