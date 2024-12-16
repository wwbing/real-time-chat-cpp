#pragma once
#include "global_header.h"


class CServer : public std::enable_shared_from_this<CServer>
{
public:
    CServer(boost::asio::io_context& ioc, unsigned short& port);
    void Start();

private:
    tcp::acceptor _acceptor;
    net::io_context& _ioc;  //io_context因为只有一个实例，所以是引用类型
    tcp::socket _socket;

};

