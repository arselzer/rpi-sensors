.PHONY: all humidity

all: humidity hall

humidity:
	gcc -std=c99 -lwiringPi humidity.c -o humidity

hall:
	gcc -std=c99 -lwiringPi hall.c -o hall
