CC = gcc
CFLAGS =-Wall -lwiringPi -lrt -lpthread
RM := rm -rf

OBJECTS = pwm.o pid.o adc.o registers.o main.o ads1115.o i2c.o timer.o service.o server.o rpiservo.o
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

ads1115.o: Framework/modules/ads1115.c
	$(CC) $(CFLAGS) -c $< -o $@

i2c.o: Framework/modules/i2c.c
	$(CC) $(CFLAGS) -c $< -o $@

timer.o: Framework/modules/timer.c
	$(CC) $(CFLAGS) -c $< -o $@

service.o: Framework/modules/service.c
	$(CC) $(CFLAGS) -c $< -o $@

server.o: Framework/modules/server.c
	$(CC) $(CFLAGS) -c $< -o $@

rpiservo.o: Framework/modules/rpiservo.c
	$(CC) $(CFLAGS) -c $< -o $@

main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	-$(RM) *.o all
.PHONY: all clean dependents
