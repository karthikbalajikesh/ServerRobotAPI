#pragma once

#include "message.hpp"
#include<iostream>
#include<boost/asio.hpp>
#include<string>
#include<vector>
#include<utility>

#define IOCONTEXT boost::asio::io_context
#define IPADDRESSv4 boost::asio::ip::address_v4
#define ENDPOINT boost::asio::ip::tcp::endpoint
#define SOCKET boost::asio::ip::tcp::socket
#define ACCEPTOR boost::asio::ip::tcp::acceptor

class TCP{
  public:
        std::shared_ptr<IOCONTEXT> IO;
        std::shared_ptr<ENDPOINT> EP;
        std::shared_ptr<ACCEPTOR> Acceptor;
        std::shared_ptr<SOCKET> SOCK;
        int BACKLOG_SIZE;

    TCP();

};