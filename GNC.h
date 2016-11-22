#pragma once

#include "helper_3dmath.h"
#include "MPU6050.h"

class GNC {
    public:
        GNC();
        ~GNC();

        void step(); // TODO add setpoints to this function
        // TODO determine if we need to understand quaternions better to be
        // able to determine what the setpoint is when you want to go forward
        // or left/right

    private:
        MPU6050 mpu;
        // MPU control/status vars
        bool dmpReady;
        uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
        uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
        uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
        uint16_t fifoCount;     // count of all bytes currently in FIFO
        uint8_t fifoBuffer[64]; // FIFO storage buffer

        // orientation/motion vars
        Quaternion q;           // [w, x, y, z]         quaternion container

};
