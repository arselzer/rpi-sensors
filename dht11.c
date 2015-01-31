#include <wiringPi.h>
#include <stdio.h>
#include "sensors.h"

#define DHTPIN 21

/*

  GND  5V GPIO5
   |   |   |
  -----------
   upper side (blue thing)
*/

int main (void) {
  wiringPiSetup();

	while (1)  {
    float *data = read_dht11(DHTPIN);

    if (data != NULL) {
      printf("temperature: %.1f °C, humidity %.1f %\n", data[0], data[1]);
    }

		delay(200);
    // 1s is the max sampling rate, but it fails quite often
	}

	return 0 ;
}
