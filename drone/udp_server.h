#pragma once

//#include <iostream>
#include <fstream>
#include <boost/asio.hpp>
#include <boost/array.hpp>

#include "comms.h"

class udp_server
{
public:
    udp_server(boost::asio::io_service&, int period);
    ~udp_server();
    void time_to_receive(const boost::system::error_code& error);
    void do_receive();
    void handle_receive(const boost::system::error_code& error, size_t);
    void start();

private:
    int period;
    boost::asio::io_service& io_service;
    boost::asio::ip::udp::socket socket;
    boost::asio::ip::udp::endpoint receiver_endpoint;
    boost::asio::deadline_timer timer;
    //boost::array<char, 1024> recv_buffer;
    boost::array<ui::data_t, 10> recv_buffer;
    //void* recv_buffer;

    // log file
    std::ofstream log_file;
};
