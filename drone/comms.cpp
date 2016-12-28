#include <cstdint>
#include <iostream>
#include <mutex>
#include <boost/thread.hpp>

#include "comms.h"
#include "pi_types.h"
#include "udp_server.h"

std::mutex Comms::ui_mutex;
ui::message_t Comms::ui_message  = ui::none;
uint8_t Comms::ui_throttle = 0;
int8_t  Comms::ui_yaw      = 0;
int8_t  Comms::ui_pitch    = 0;
int8_t  Comms::ui_roll     = 0;

Comms::Comms(int period) : period(period), server(period)
{
    //boost::asio::io_service::work wrk(ios);
    //server = udp_server(ios, period);
    //thr = new boost::thread(server.start());
    //boost::shared_ptr< boost::thread >( new boost::thread( server.start()) );
    thread = new boost::thread (&udp_server::start, &server);
    //boost::thread t(server.start());
    //ios.run();
}

ret_code_t Comms::initialize()
{
    return success;
}

void Comms::step()
{

}

void Comms::set_ui(ui::message_t m, uint8_t t, int8_t  y, int8_t  p, int8_t  r)
{
    std::lock_guard<std::mutex> guard(ui_mutex);
    ui_message = m;
    ui_throttle = t;
    ui_yaw = y;
    ui_pitch = p;
    ui_roll = r;
}

ui::data_t* Comms::get_ui()
{
    std::lock_guard<std::mutex> guard(ui_mutex);
    ui::data_t* d = new ui::data_t(ui_message, ui_throttle, ui_yaw, ui_pitch, ui_roll);

    return d;
}

// void Comms::send_message(std::string data)
// {
//     server.send_message(data);
// }
