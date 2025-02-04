#pragma once
#include "const.h"

/*
	HttpConnection��������ӵ����ݶ�д
	�յ��ͻ���������Ƚ�����ת����LogicSystem���д���
	���������HttpConnection�ظ��ͻ�����Ϣ��
*/
class HttpConnection: public std::enable_shared_from_this<HttpConnection>
{
	friend class LogicSystem;
public:
	HttpConnection(boost::asio::io_context& ioc);

	void Start();	//�����첽��ȡ�ͻ��˷�����������

	void PreParseGetParam();

	tcp::socket& GetSocket() {
		return _socket;
	}

private:
	void CheckDeadline();
	void WriteResponse();
	void HandleReq();

	tcp::socket  _socket;	//!!!�������� _socket

	beast::flat_buffer  _buffer{ 8192 };	//������buffer

	http::request<http::dynamic_body> _request;		//��������

	http::response<http::dynamic_body> _response;	//��Ӧ����

	net::steady_timer deadline_{_socket.get_executor(), std::chrono::seconds(60) }; //��ʱ��

	std::string _get_url; //url

	std::unordered_map<std::string, std::string> _get_params; //��Ϣ����
};

