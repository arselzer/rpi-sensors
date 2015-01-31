#include <wiringPi.h>
#include <math.h>

#define CONTROL_PIN 22

int main() {
  wiringPiSetup();
  pinMode(CONTROL_PIN, OUTPUT);

  int i = M_PI;
  while (1) {
    digitalWrite(CONTROL_PIN, HIGH);
    delay(300 + round(sin(i / 2) * 100));
    digitalWrite(CONTROL_PIN, LOW);
    delay(300 + round(sin(i / 2) * 100));

    i++;
  }

  return 0;
}
