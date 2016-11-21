#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "GNC.h"

GNC gnc;

// ================================================================
// ===                      INITIAL SETUP                       ===
// ================================================================
void setup() {
}

// ================================================================
// ===                    MAIN PROGRAM LOOP                     ===
// ================================================================

void loop() {
    gnc.step();
}

int main() {
    setup();
    usleep(100000);
    for (;;)
        loop();

    return 0;
}
