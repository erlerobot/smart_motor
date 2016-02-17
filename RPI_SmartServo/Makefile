CC = gcc
CFLAGS =-Wall -lwiringPi

OBJECTS = pwm.o pid.o adc.o registers.o main.o
OUT = SmartServo


#all: target -> This is the default target for makefiles.
all : $(OBJECTS)	
	$(CC) $(CFLAGS) -o $(OUT) $(OBJECTS)

adc.o: Framework/modules/adc.c
	$(CC) $(CFLAGS) -c $< -o $@

pid.o: Framework/modules/pid.c
	$(CC) $(CFLAGS) -c $< -o $@

pwm.o: Framework/modules/pwm.c
	$(CC) $(CFLAGS) -c $< -o $@

registers.o: Framework/modules/registers.c
	$(CC) $(CFLAGS) -c $< -o $@

main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm *o hello