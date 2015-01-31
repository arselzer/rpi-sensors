all: dht11 temperature adc obstacle
	
dht11:
	gcc -Wall -std=c99 -lwiringPi dht11.c sensors.c -o dht11

temperature:
	gcc -Wall -std=c99 -lwiringPi temperature.c sensors.c -o temperature

adc:
	gcc -Wall -std=c99 -lwiringPi adc.c sensors.c -o adc

obstacle:
	gcc -Wall -std=c99 -lwiringPi obstacle.c sensors.c -o obstacle

relay:
	gcc -Wall -lwiringPi -lm -Wall relay.c -o relay

.PHONY: all dht11 temperature adc obstacle relay
