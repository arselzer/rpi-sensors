#include <wiringPi.h>
#include <stdio.h>
#include "sensors.h"

/*
ADC chip:

(half circle up here)
* CS  -      - Vcc
  CH0 -      - CLK *
  CH1 -      - DO
  GND -      - DI *


Use CH1 as input, and DO as output. For some reason this is the only thing that works for me.
*/

#define     ADC_CS    23
#define     ADC_CLK   24
#define     ADC_DIO   25

int main (void) {
  wiringPiSetup();

	while (1)  {
    unsigned char data = read_adc0832(ADC_CS, ADC_CLK, ADC_DIO);

    printf("%d \n", data);

		delay(500);
	}

	return 0;
}
