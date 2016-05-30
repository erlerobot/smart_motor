CC = gcc
CFLAGS =-Wall -lwiringPi -lrt -lpthread

OBJECTS = ads1115.o i2c.o Timer.o
OUT = TimerADS1115


#all: target -> This is the default target for makefiles.
all : $(OBJECTS)	
	$(CC) $(CFLAGS) -o $(OUT) $(OBJECTS)


ads1115.o: ads1115.c
	$(CC) $(CFLAGS) -c $< -o $@

i2c.o: i2c.c
	$(CC) $(CFLAGS) -c $< -o $@

Timer.o: Timer.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm *o hello
