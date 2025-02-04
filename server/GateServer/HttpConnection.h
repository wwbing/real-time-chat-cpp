#pragma once
#include "const.h"

/*
	HttpConnection类管理连接的数据读写
	收到客户端请求后，先解析再转发给LogicSystem进行处理
	处理结束后，HttpConnection回复客户端信息。
*/
class HttpConnection: public std::enable_shared_from_this<HttpConnection>
{
	friend class LogicSystem;
public:
	HttpConnection(boost::asio::io_context& ioc);

	void Start();	//开启异步读取客户端发送来的数据

	void PreParseGetParam();

	tcp::socket& GetSocket() {
		return _socket;
	}

private:
	void CheckDeadline();
	void WriteResponse();
	void HandleReq();

	tcp::socket  _socket;	//!!!该类管理的 _socket

	beast::flat_buffer  _buffer{ 8192 };	//缓冲区buffer

	http::request<http::dynamic_body> _request;		//请求数据

	http::response<http::dynamic_body> _response;	//回应数据

	net::steady_timer deadline_{_socket.get_executor(), std::chrono::seconds(60) }; //定时器

	std::string _get_url; //url

	std::unordered_map<std::string, std::string> _get_params; //消息参数
};

