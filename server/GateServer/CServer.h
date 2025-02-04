#pragma once
#include <string>
#include "const.h"
/*
	CServer�����ڼ���ָ���˿ںš����Կͻ��˵�����
*/

class CServer:public std::enable_shared_from_this<CServer>
{
public:
	CServer(boost::asio::io_context& ioc, unsigned short& port);
	void Start();		//������ʼ

private:
	tcp::acceptor  _acceptor;	//���ڼ����� tcp::acceptor
	net::io_context& _ioc;
	
};

