#include <wiringPi.h>
#include <stdio.h>
#include "sensors.h"

/*
ADC chip:

(half circle up here)
* CS  -      - Vcc
  CH0 -      - CLK *
  CH1 -      - DO *
  GND -      - DI 

Analog Temperature Sensor:

    |   |   |
   CH1  3v  GND

   DO = ADC_DIO
*/

#define     ADC_CS    23
#define     ADC_CLK   24
#define     ADC_DIO   25

int main (void) {
  wiringPiSetup();

	while (1)  {
    unsigned char data = read_adc0832(ADC_CS, ADC_CLK, ADC_DIO);

    char temperature = 60 - data;
    printf("%d °C\n", temperature);

		delay(500);
	}

	return 0;
}
