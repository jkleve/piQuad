#include <ctime>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <boost/thread.hpp>
#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <mutex>

#include "comms.h"
#include "udp_server.h"

using boost::asio::ip::udp;

std::string make_daytime_string()
{
  using namespace std; // For time_t, time and ctime;
  time_t now = time(0);
  return ctime(&now);
}

udp_server::udp_server(boost::asio::io_service& ios, int period)
    : period(period),
      io_service(ios),
      socket(io_service, {udp::v4(), 3643}),
      timer(io_service, boost::posix_time::milliseconds(period))
{
    // skip all the messages we missed
    boost::asio::socket_base::receive_buffer_size option(0);
    socket.set_option(option);
    // request first receive
    //do_receive();

    log_file.open ("example.txt");
}

udp_server::~udp_server()
{
    log_file.close();
}

void udp_server::time_to_receive(const boost::system::error_code& error)
{
    do_receive();
}

void udp_server::start()
{
    #ifdef DEBUG
    std::cout << "-=| server starting |=-" << std::endl;
    #endif
    do_receive();
    io_service.run();
}

void udp_server::do_receive()
{
    #ifdef DEBUG
    std::cout << "-=| server requesting receive |=-" << std::endl;
    #endif
    socket.async_receive_from(boost::asio::buffer(recv_buffer), receiver_endpoint,
                               boost::bind(&udp_server::handle_receive, this,
                               boost::asio::placeholders::error,
                               boost::asio::placeholders::bytes_transferred));
}

void udp_server::handle_receive(const boost::system::error_code& error, size_t bytes_transferred)
{
    #ifdef DEBUG
    std::cout << "-=| received message |=-" << std::endl;
    #endif
    //std::string* str = new std::string(make_daytime_string());
    //str->erase(std::remove(str->begin(), str->end(), '\n'), str->end());
    //boost::shared_ptr<std::string> message(str);
    // std::cout << *str
    //           << ": "
    //           << std::string(recv_buffer.begin(), recv_buffer.begin()+bytes_transferred)
    //           << std::endl;
    ui::data_t data = recv_buffer[0];
    ui::message_t m = data.message;
    uint8_t t = data.throttle;
    int8_t y = data.yaw;
    int8_t p = data.pitch;
    int8_t r = data.roll;

    log_file << "Throttle: " << t << ", yaw: " << y << ", pitch: " << p << ", roll: " << r << std::endl;

    timer.expires_from_now(boost::posix_time::milliseconds(100));
    timer.async_wait(boost::bind(&udp_server::time_to_receive, this,
                                 boost::asio::placeholders::error));

    // TODO mutex lock ui variables
    //std::lock_guard<std::mutex> guard(ui_mutex);
    // ui_throttle = 0;
    // ui_yaw = 0;
    // ui_pitch = 0;
    // ui_roll = 0;
    Comms::set_ui(m, t, y, p, r);
}

// void server()
// {
//   boost::asio::io_service ios;
//   boost::asio::io_service::work wrk(ios);
//   udp_server updclient(ios);
//   ios.run();
// }

// int main()
// {
//   boost::thread t(server);
//   std::cout << "here" << std::endl;
//   int i;
//   while(true)
//     i++;
//   return 0;
// }
