#include "tcp.h"

#define IOCONTEXT boost::asio::io_context
#define IPADDRESSv4 boost::asio::ip::address_v4
#define ENDPOINT boost::asio::ip::tcp::endpoint
#define SOCKET boost::asio::ip::tcp::socket
#define ACCEPTOR boost::asio::ip::tcp::acceptor

TCP::TCP(){
    IO = std::make_shared<IOCONTEXT>();
    BACKLOG_SIZE = 30;
    unsigned int port_num = 5000;
    EP = std::make_shared<ENDPOINT>(IPADDRESSv4::any(),port_num);
    try{
        Acceptor = std::make_shared<ACCEPTOR>(*IO,EP->protocol());
        Acceptor->bind(*EP);
        
    }catch(boost::system::system_error &e){
        std::cout<<e.what();
    }

}