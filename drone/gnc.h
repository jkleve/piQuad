#pragma once

#include "helper_3dmath.h"
#include "MPU6050.h"
#include "comms.h"
#include "rpiPWM1.h"

class GNC {
    public:
        GNC();
        ~GNC();

        void initialize();
        void step(ui::data_t*); // TODO add setpoints to this function
        // TODO determine if we need to understand quaternions better to be
        // able to determine what the setpoint is when you want to go forward
        // or left/right

    private:
        MPU6050 mpu;
        rpiPWM1 pwm;
        // MPU control/status vars
        bool dmpReady;
        uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
        uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
        uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
        uint16_t fifoCount;     // count of all bytes currently in FIFO
        uint8_t fifoBuffer[64]; // FIFO storage buffer

        uint8_t set_throttle;
        int8_t  set_yaw;
        int8_t  set_pitch;
        int8_t  set_roll;

        // orientation/motion vars
        Quaternion q;           // [w, x, y, z]         quaternion container

        //udp_server
};
