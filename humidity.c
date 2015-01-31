#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAXTIMINGS 85

#define DHTPIN 21

float *read_dht11(int pin) {
	uint8_t laststate = HIGH;
	uint8_t j = 0;

  int dht11_dat[5] = {0,0,0,0,0};

  /* initialize the sensors */

	// pull pin down for 18 milliseconds
	pinMode(pin, OUTPUT);
	digitalWrite(pin, LOW);
	delay(18);
	
  // then pull it up for 40 microseconds
	digitalWrite(pin, HIGH);
	delayMicroseconds(40); 
	
  pinMode(pin, INPUT);

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
		if ((i >= 4) && (i%2 == 0)) {
			// shove each bit into the storage bytes
			dht11_dat[j/8] <<= 1;
			if (counter > 16)
				dht11_dat[j/8] |= 1;
			j++;
		}
	}

	// check we read 40 bits (8bit x 5 ) + verify checksum in the last byte
	if ((j >= 40) && (dht11_dat[4] == ((dht11_dat[0] + dht11_dat[1] + dht11_dat[2] + dht11_dat[3]) & 0xFF)) ) {
    float humidity = dht11_dat[0] + dht11_dat[1] * 0.1;
    float temperature = dht11_dat[2] + dht11_dat[3] * 0.1;

    float data[] = {humidity, temperature};
    return &data;
	}
	else
	{
		//printf("Data not good, skip\n");
    return NULL;
	}
}

int main (void) {
  wiringPiSetup();

	while (1)  {
		float *data = read_dht11(DHTPIN);

    if (data != NULL) {
      printf("temperature: %.1f °C, humidity %.1f %\n", data[0], data[1]);
    }
    //else {
    //  printf(":/\n");
    //}

		delay(200);
	}

	return 0 ;
}
