//
// blocking_udp_echo_client.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2015 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <algorithm>
#include <ctime>
#include <string>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>

#include "../drone/comms.h"

using boost::asio::ip::udp;

enum { max_length = 1024 };

std::string make_daytime_string()
{
  using namespace std; // For time_t, time and ctime;
  time_t now = time(0);
  return ctime(&now);
}

int main(int argc, char* argv[])
{
  try
  {

    //std::string addr = "localhost";
    std::string addr = "192.168.0.29";
    std::string port = "3643";

    boost::asio::io_service io_service;
    char reply[max_length];
    udp::endpoint sender_endpoint;

    udp::socket s(io_service, udp::endpoint(udp::v4(), 0));

    udp::resolver resolver(io_service);
    udp::endpoint endpoint = *resolver.resolve({udp::v4(), addr, port});

    // connect
    //std::cout << "Hit enter to connect";
    //std::cin.getline(reply, max_length);
    //std::cout << std::endl;
    char request[max_length] = "Request Connection.\0";
    size_t request_length = std::strlen(request);
    // s.send_to(boost::asio::buffer(request, request_length), endpoint); TODO removed this because we need to fix server to accept the initial connect request

    // receive confirmation
    // size_t reply_length = s.receive_from(
    //     boost::asio::buffer(reply, max_length), sender_endpoint);
    // std::cout << "Connected: ";
    // std::cout.write(reply, reply_length);
    // std::cout << std::endl;

    int i = 0;

    while (true)
    {
        // send message

        const ui::data_t* d = new ui::data_t(ui::none, ++i, 0, 0, 0);
        const void* v = d;

        //std::string* str = new std::string(make_daytime_string());
        //str->erase(std::remove(str->begin(), str->end(), '\n'), str->end());
        //boost::shared_ptr<std::string> message(str);
        //std::cout << "Send message: ";
        //std::cin.getline(reply, max_length);
        //std::cout << std::endl;
        std::cout << "Sending message ..." << std::endl;
        //s.send_to(boost::asio::buffer(*message), endpoint);
        s.send_to(boost::asio::buffer(v, sizeof(*d)), endpoint);
        boost::this_thread::sleep(boost::posix_time::milliseconds(50));
        // get response
        // std::cout << "Waiting for response ..." << std::endl;
        // size_t reply_length = s.receive_from(
        //     boost::asio::buffer(reply, max_length), sender_endpoint);
        // std::cout << "Reply is: ";
        // std::cout.write(reply, reply_length);
        // std::cout << "\n";
    }
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
