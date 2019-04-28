CC = g++
CFLAGS = -g3 -O3 -Wall -std=c++11

all:
	$(CC) $(CFLAGS) src/appointment.cpp -c -o src/appointment.o
	$(CC) $(CFLAGS) src/agenda.cpp -c -o src/agenda.o
	$(CC) $(CFLAGS) src/main.cpp -c -o src/main.o
	$(CC) $(CFLAGS) -o tp1 src/main.o src/appointment.o src/agenda.o
	rm src/*.o

clean:
	rm src/*.o
