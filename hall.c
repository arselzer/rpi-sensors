#include <wiringPi.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char **argv) {
	const int led = 21;
	const int sensor = 22;
	
	wiringPiSetup();
	
	pinMode(led, OUTPUT);
	pinMode(sensor, INPUT);

	int detected = 0;

	while (1) {
		int value = digitalRead(sensor);

		//if (value == 1) {
		//	printf("%i, %i ", value, detected);
		//}

		if (value == 1 && detected == 0) {
			detected = 1;
			printf("detected\n");
		}

		if (detected == 1 && value == 0) {
			detected = 0;
		}
	}

	return 0;
}
