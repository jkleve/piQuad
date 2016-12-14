//
// blocking_udp_echo_server.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2015 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

enum { max_length = 1024 };

void server(boost::asio::io_service& io_service, unsigned short port)
{
  //udp::socket sock;
  udp::endpoint endpoint;
  udp::endpoint sender_endpoint;

  endpoint = udp::endpoint(udp::v4(), port);
  udp::socket sock = udp::socket(io_service, endpoint);

  for (;;)
  {
    char data[max_length];
    std::cout << sender_endpoint.address() << std::endl;
    size_t length = sock.receive_from(boost::asio::buffer(data, max_length), sender_endpoint);
    std::cout << sender_endpoint.address() << std::endl;
    sock.send_to(boost::asio::buffer(data, length), sender_endpoint);
  }
}

int main(int argc, char* argv[])
{
  unsigned short port = 3643;
  try
  {
    boost::asio::io_service io_service;

    server(io_service, port);
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
