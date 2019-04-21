.PHONY: clean

C = gcc

obj-m += project1.o
project1-objs := main.o process.o schedule.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	
main.o: main.c
	$(C) main.c -c

process.o: process.c process.h
	$(C) process.c -c

schedule.o: schedule.c schedule.h
	$(C) schedule.c -c

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm *.o main





	