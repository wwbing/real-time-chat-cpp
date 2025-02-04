#include "CServer.h"
#include <iostream>
#include "AsioIOServicePool.h"
#include "UserMgr.h"

//构造后就开启异步监听
CServer::CServer(boost::asio::io_context& io_context, short port):
	_io_context(io_context),
	_port(port),
	_acceptor(io_context, tcp::endpoint(tcp::v4(),port))
{
	cout << "Server start success, listen on port : " << _port << endl;
	StartAccept();
}

CServer::~CServer() {
	cout << "Server destruct listen on port : " << _port << endl;
}

//监听到就调用此函数建立连接
void CServer::HandleAccept(shared_ptr<CSession> new_session, const boost::system::error_code& error){
	if (!error) {

		//开启对应会话的读写监听
		new_session->Start();
		lock_guard<mutex> lock(_mutex);
		_sessions.insert(make_pair(new_session->GetSessionId(), new_session));
	}
	else {
		cout << "session accept failed, error is " << error.what() << endl;
	}

	StartAccept();
}

void CServer::StartAccept() {
	//从连接池中取出一个ioc用于创建具体的session会话
	auto &io_context = AsioIOServicePool::GetInstance()->GetIOService();
	shared_ptr<CSession> new_session = make_shared<CSession>(io_context, this);

	/*
		使用bind为的是满足async_accept回调函数的函数签名
		acceptor.async_accept(socket, accept_handler);
		注意这里bind的是成员函数，成员函数都有一个默认的参数是对象的地址
	*/
	_acceptor.async_accept(
		new_session->GetSocket(),
		std::bind(&CServer::HandleAccept, this, new_session, placeholders::_1)
	);
}

void CServer::ClearSession(std::string uuid) {
	
	if (_sessions.find(uuid) != _sessions.end()) {
		//移除用户和session的关联
		UserMgr::GetInstance()->RmvUserSession(_sessions[uuid]->GetUserId());
	}

	{
		lock_guard<mutex> lock(_mutex);
		_sessions.erase(uuid);
	}
	
}
