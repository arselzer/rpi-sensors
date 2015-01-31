#include <wiringPi.h>
#include <stdio.h>
#include <unistd.h>

#define SENSOR_PIN 22

void onProximity() {
  printf("on no! crash. maybe.\n");
}

int main () {
  wiringPiSetup();

  if (wiringPiISR(SENSOR_PIN, INT_EDGE_FALLING, &onProximity) < 0) {
    fprintf(stderr, "error\n");
    return 1;
  }

  while (1) {
    sleep(1);
  }

  return 0;
}
