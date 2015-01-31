all:
	gcc -std=c99 -lwiringPi main.c sensors.c -o log
