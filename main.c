#include <wiringPi.h>
#include <stdio.h>
#include "sensors.h"

#define DHTPIN 21

int main (void) {
  wiringPiSetup();

	while (1)  {
    float *data = read_dht11(DHTPIN);

    if (data != NULL) {
      printf("temperature: %.1f °C, humidity %.1f %\n", data[0], data[1]);
    }

		delay(1000);
    // 1s is the max sampling rate
	}

	return 0 ;
}
