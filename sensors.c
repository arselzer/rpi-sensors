#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "sensors.h"

#define MAXTIMINGS 85

/*
 *  Adapted from Sunfounder Sensor Kit
 *  returns NULL if the data is bad.
 */

float *read_dht11(int pin) {
	uint8_t bitsRead = 0;

  int data[5] = {0,0,0,0,0};

  /* initialize the sensors */

	// pull pin down for 18 milliseconds
	pinMode(pin, OUTPUT);
	digitalWrite(pin, LOW);
	delay(18);
	
  // then pull it up for 40 microseconds
	digitalWrite(pin, HIGH);
	delayMicroseconds(40); 

  pinMode(pin, INPUT);

	uint8_t laststate = HIGH;
	uint8_t counter = 0;

	// detect change and read data
	for (int i = 0; i < MAXTIMINGS; i++) {
		counter = 0;

		while (digitalRead(pin) == laststate) {
			counter++;
			delayMicroseconds(1);
			if (counter == 255) {
				break;
			}
		}

		laststate = digitalRead(pin);

		if (counter == 255) break;

		// ignore first 3 transitions
		if ((i >= 4) && (i % 2 == 0)) {
      // put the bytes into the data array
			data[bitsRead / 8] <<= 1;
			if (counter > 16)
				data[bitsRead / 8] |= 1;
			bitsRead++;
		}
	}

	// check if 40 bits were read (5x8 bits) + verify checksum in the last byte
  int dataIsOk = (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF));

	if ((bitsRead >= 40) && dataIsOk) {
    float humidity = data[0] + data[1] * 0.1;
    float temperature = data[2] + data[3] * 0.1;

    static float result[2]; //{humidity, temperature};
    result[0] = humidity;
    result[1] = temperature;
    return result;
	}
	else {
    return NULL;
	}
}

/*
 *  Adapted from Sunfounder Sensor Kit
 *  Might or might not work well. Can't be sure because I think my ADC broke.
 *  python version that seems much simpler: http://heinrichhartmann.com/2014/12/14/Sensor-Monitoring-with-RaspberryPi-and-Circonus.html
 */

unsigned char read_adc0832(int adc_cs, int adc_clk, int adc_dio) {
  pinMode(adc_cs, OUTPUT);
  pinMode(adc_clk, OUTPUT);
  pinMode(adc_dio, OUTPUT);

	digitalWrite(adc_cs, 0);
	digitalWrite(adc_clk,0);
	digitalWrite(adc_dio,1);	delayMicroseconds(2);
	digitalWrite(adc_clk,1);	delayMicroseconds(2);

	digitalWrite(adc_clk,0);	
	
  digitalWrite(adc_dio,1);  delayMicroseconds(2);
	digitalWrite(adc_clk,1);  delayMicroseconds(2);
	digitalWrite(adc_clk,0);	

	digitalWrite(adc_dio,0);  delayMicroseconds(2);
	digitalWrite(adc_clk,1);	

	digitalWrite(adc_dio,1);  delayMicroseconds(2);
	digitalWrite(adc_clk,0);	

	digitalWrite(adc_dio,1);  delayMicroseconds(2);

  unsigned char dat1 = 0, dat2 = 0;

	for(int i = 0; i < 8; i++) {
		digitalWrite(adc_clk,1); delayMicroseconds(2);
		digitalWrite(adc_clk,0); delayMicroseconds(2);

		pinMode(adc_dio, INPUT);
		dat1 = dat1 << 1 | digitalRead(adc_dio);
	}
	
	for(int i = 0; i < 8; i++) {
		dat2 = dat2 | ((unsigned char) digitalRead(adc_dio) << i);

		digitalWrite(adc_clk,1); 	delayMicroseconds(2);
		digitalWrite(adc_clk,0);  delayMicroseconds(2);
	}

  // reset
	digitalWrite(adc_cs,1);
	
	return (dat1 == dat2) ? dat1 : 0;
}

