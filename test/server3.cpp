#include <ctime>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <boost/thread.hpp>
#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>

using boost::asio::ip::udp;

std::string make_daytime_string()
{
  using namespace std; // For time_t, time and ctime;
  time_t now = time(0);
  return ctime(&now);
}


class UDPClient
{
public:
    boost::asio::io_service& io_service;
    udp::socket socket;
    udp::endpoint receiver_endpoint;
    boost::asio::deadline_timer timer;
    boost::array<char, 1024> recv_buffer;

    UDPClient(boost::asio::io_service&);
    void time_to_receive(const boost::system::error_code& error);
    void do_receive();
    void handle_receive(const boost::system::error_code& error, size_t);
    void start();
};

UDPClient::UDPClient(boost::asio::io_service& ios)
    : io_service(ios),
      socket(io_service, {udp::v4(), 3643}),
      timer(io_service, boost::posix_time::milliseconds(100))
{
    boost::asio::socket_base::receive_buffer_size option(0);
    socket.set_option(option);
    //do_receive();
}

void UDPClient::start()
{
    do_receive();
    io_service.run();
}

void UDPClient::time_to_receive(const boost::system::error_code& error)
{
    do_receive();
}

void UDPClient::do_receive()
{
    socket.async_receive_from(boost::asio::buffer(recv_buffer), receiver_endpoint,
                               boost::bind(&UDPClient::handle_receive, this,
                               boost::asio::placeholders::error,
                               boost::asio::placeholders::bytes_transferred));
}

void UDPClient::handle_receive(const boost::system::error_code& error, size_t bytes_transferred)
{
    std::string* str = new std::string(make_daytime_string());
    str->erase(std::remove(str->begin(), str->end(), '\n'), str->end());
    boost::shared_ptr<std::string> message(str);
    std::cout << *str
              << ": "
              << std::string(recv_buffer.begin(), recv_buffer.begin()+bytes_transferred)
              << std::endl;
    timer.expires_from_now(boost::posix_time::milliseconds(100));
    timer.async_wait(boost::bind(&UDPClient::time_to_receive, this,
                                 boost::asio::placeholders::error));
}

void server()
{
  boost::asio::io_service ios;
  boost::asio::io_service::work wrk(ios);
  UDPClient updclient(ios);
  ios.run();
}

int main()
{
  boost::asio::io_service ios;
  boost::asio::io_service::work wrk(ios);
  server = UDPClient(ios);
  boost::thread t(server.start());
  std::cout << "here" << std::endl;
  int i;
  while(true)
    i++;
  return 0;
}
