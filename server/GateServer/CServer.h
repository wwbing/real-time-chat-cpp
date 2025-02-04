#pragma once
#include <string>
#include "const.h"
/*
	CServer类用于监听指定端口号。来自客户端的连接
*/

class CServer:public std::enable_shared_from_this<CServer>
{
public:
	CServer(boost::asio::io_context& ioc, unsigned short& port);
	void Start();		//监听开始

private:
	tcp::acceptor  _acceptor;	//用于监听的 tcp::acceptor
	net::io_context& _ioc;
	
};

