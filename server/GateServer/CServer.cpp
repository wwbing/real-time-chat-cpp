#include "CServer.h"
#include <iostream>
#include "HttpConnection.h"
#include "AsioIOServicePool.h"
CServer::CServer(boost::asio::io_context& ioc, unsigned short& port) :
	_ioc(ioc),
	_acceptor(ioc, tcp::endpoint(tcp::v4(), port))
{

}

//开始监听
void CServer::Start()
{	
	auto self = shared_from_this(); //防止self的生命周期在被子线程使用过程中结束

	/*
	*	从连接池中取出一个ioc，将该ioc交给HttpConnection类管理
	*	HttpConnection内部会创建该ioc的socket作为async_accept的参数
	*/
	auto& io_context = AsioIOServicePool::GetInstance()->GetIOService();
	std::shared_ptr<HttpConnection> new_con = std::make_shared<HttpConnection>(io_context);

	//异步监听:异步都不会阻塞，会全部把线程池的ioc用http类管理并开启监听
	_acceptor.async_accept(
		new_con->GetSocket(), 
		[self, new_con](beast::error_code ec) {
			try {
				//出错则放弃这个连接，继续监听新链接
				if (ec) {
					self->Start();
					return;
				}

				//处理新链接，创建HpptConnection类管理新连接
				new_con->Start();
				//继续监听
				self->Start();
			}
			catch (std::exception& exp) {
				std::cout << "exception is " << exp.what() << std::endl;
				self->Start();
			}
		}
	);
}


