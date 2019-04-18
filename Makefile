.PHONY: clean

C = gcc




all: main.o process.o schedule.o
	$(C) main.o process.o schedule.o -o main
	
main.o: main.c
	$(C) main.c -c

process.o: process.c process.h
	$(C) process.c -c

schedule.o: schedule.c schedule.h
	$(C) schedule.c -c

clean:
	$(RM) *.o main
