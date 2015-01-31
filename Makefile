.PHONY: all humidity

all:
	gcc laser.c -lwiringPi -o laser
	gcc led.c -lwiringPi -o led
	gcc hall.c -lwiringPi -o hall

humidity:
	gcc -lwiringPi humidity.c -o humidity
	
