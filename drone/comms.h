#pragma once

#include <mutex>
#include <boost/thread.hpp>

#include "pi_types.h"

namespace ui { // TODO syntax?
    enum message_t {
        none,
        calibrate,
        arm,
        disarm
    };

    struct data_t {
        data_t(message_t m, uint8_t t, int8_t y, int8_t p, int8_t r) :
            message(m), throttle(t), yaw(y), pitch(p), roll(r) {}
        data_t() : message(none), throttle(0), yaw(0), pitch(0), roll(0) {}
        message_t message;
        uint8_t throttle;
        int8_t yaw;
        int8_t pitch;
        int8_t roll;
    };
};

// extern ui::message_t ui_message;
// extern uint8_t ui_throttle;
// extern int8_t ui_yaw;
// extern int8_t ui_pitch;
// extern int8_t ui_roll;
#include "udp_server.h"

class Comms
{
    public:
        Comms(int period);
        ret_code_t initialize();
        void step();
        void send_message(std::string data);
        static void set_ui(ui::message_t m,
                    uint8_t t,
                    int8_t  y,
                    int8_t  p,
                    int8_t  r);
        static ui::data_t* get_ui();

    private:
        static std::mutex ui_mutex;
        static ui::message_t ui_message;
        static uint8_t ui_throttle;
        static int8_t ui_yaw;
        static int8_t ui_pitch;
        static int8_t ui_roll;

        //boost::asio::io_service ios;
        int period;
        udp_server server;
        boost::thread* thread;
};
