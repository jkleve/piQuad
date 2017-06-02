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
#include <string>
//#include <boost/optional.hpp>
//#include <boost/ref.hpp>
//#include <boost/utility/in_place_factory.hpp>
#include <boost/make_shared.hpp>
#include <boost/thread/thread.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

enum { max_length = 1024 };

void receive_handler(const boost::system::error_code& error, size_t received_bytes)
{
    std::cout << "Received something!!!" << std::endl;
}

int string_len(const char* s, int max_len)
{
    int i = 0;
    while (s[i] != '\0')
    {
        i++;
    }
    return i;
}

void server(boost::asio::io_service& io_service, unsigned short port)
{
  //udp::socket sock;
  udp::endpoint endpoint;
  udp::endpoint sender_endpoint;
  char data[max_length];

  endpoint = udp::endpoint(udp::v4(), port);
  udp::socket sock = udp::socket(io_service, endpoint);

  size_t length = sock.receive_from(boost::asio::buffer(data, max_length), sender_endpoint);
  std::cout << "Connected to: " << sender_endpoint.address() << std::endl;

  strcpy(data, "Welcome to piQuad Server!\0");
  length = string_len(data, max_length);
  sock.send_to(boost::asio::buffer(data, length), sender_endpoint);

  //boost::optional<boost::asio::io_service::work> work = boost::in_place(boost::ref(io_service));
  //boost::asio::io_service::work work(io_service);
  //io_service.run();

  for (;;)
  {
    boost::this_thread::sleep(boost::posix_time::seconds(1));
    sock.async_receive_from(boost::asio::buffer(data, max_length), sender_endpoint, receive_handler);
    std::cout << "Requested Receive from " << sender_endpoint << std::endl;
  }
}

int main(int argc, char* argv[])
{
  unsigned short port = 3643;
  try
  {
    boost::asio::io_service io_service;

    // boost::thread_group threads;
    // threads.create_thread(server(io_service, port));
    server(io_service, port);
    boost::thread t(boost::bind(&boost::asio::io_service::run, &io_service));
    // create fake work and start io service
    //auto work = boost::make_shared<boost::asio::io_service::work>(io_service);
    //io_service.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
