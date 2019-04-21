.PHONY: clean

C = gcc



main: main.o process.o schedule.o
	gcc main.o process.o schedule.o -o main
	
main.o: main.c
	$(C) main.c -c

process.o: process.c process.h
	$(C) process.c -c

schedule.o: schedule.c schedule.h
	$(C) schedule.c -c

clean:
	rm *.o main





	