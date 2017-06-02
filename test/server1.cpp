#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>

using boost::asio::ip::udp;

class UDPClient
{
public:
    boost::asio::io_service io_service;
    udp::socket socket;
    udp::endpoint receiver_endpoint;
    boost::asio::deadline_timer timer;
    boost::array<char, 1024> recv_buffer;

    UDPClient();
    void time_to_receive(const boost::system::error_code& error);
    void do_receive();
    void handle_receive(const boost::system::error_code& error, size_t);
};

UDPClient::UDPClient()
    : io_service(),
      socket(io_service, {udp::v4(), 3643}),
      timer(io_service, boost::posix_time::seconds(2))
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
    std::cout << "Received: '" << std::string(recv_buffer.begin(), recv_buffer.begin()+bytes_transferred) << "'\n";

    timer.async_wait(boost::bind(time_to_receive, this, boost::asio::placeholders::error));
}

int main()
{
    UDPClient updclient;
}
