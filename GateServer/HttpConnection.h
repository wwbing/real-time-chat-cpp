#pragma once

#include "global_header.h"


class HttpConnection:public std::enable_shared_from_this<HttpConnection>
{
    friend class LogicSystem;
public:
    HttpConnection(tcp::socket socket);
    void Start();

private:
    void CheckDeadline();
    void WriteResponse();
    void HandleReq();

    tcp::socket _socket;
    beast::flat_buffer _buffer{ 8192 };             //用于临时存储从_socket流中读取的数据。常用的类型是
    http::request<http::dynamic_body> _request;     //存放http客户端请求的缓冲区
    http::response<http::dynamic_body> _response;   //回应的缓冲区

    net::steady_timer deadline_{
        _socket.get_executor(), std::chrono::seconds(60)    //60秒定时器,这里用的花括号初始化(List initialization)
    };

};

