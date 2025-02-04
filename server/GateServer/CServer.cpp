#include "CServer.h"
#include <iostream>
#include "HttpConnection.h"
#include "AsioIOServicePool.h"
CServer::CServer(boost::asio::io_context& ioc, unsigned short& port) :
	_ioc(ioc),
	_acceptor(ioc, tcp::endpoint(tcp::v4(), port))
{

}

//��ʼ����
void CServer::Start()
{	
	auto self = shared_from_this(); //��ֹself�����������ڱ����߳�ʹ�ù����н���

	/*
	*	�����ӳ���ȡ��һ��ioc������ioc����HttpConnection�����
	*	HttpConnection�ڲ��ᴴ����ioc��socket��Ϊasync_accept�Ĳ���
	*/
	auto& io_context = AsioIOServicePool::GetInstance()->GetIOService();
	std::shared_ptr<HttpConnection> new_con = std::make_shared<HttpConnection>(io_context);

	//�첽����:�첽��������������ȫ�����̳߳ص�ioc��http�������������
	_acceptor.async_accept(
		new_con->GetSocket(), 
		[self, new_con](beast::error_code ec) {
			try {
				//���������������ӣ���������������
				if (ec) {
					self->Start();
					return;
				}

				//���������ӣ�����HpptConnection�����������
				new_con->Start();
				//��������
				self->Start();
			}
			catch (std::exception& exp) {
				std::cout << "exception is " << exp.what() << std::endl;
				self->Start();
			}
		}
	);
}


