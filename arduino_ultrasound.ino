#include <Wire.h>

#include "ultrasound.h"

Ults ultrasound1(D5,D6);
void setup() {
    Serial.begin(115200);
}

void loop() {
    Serial.println(ultrasound1.get_val());
}
