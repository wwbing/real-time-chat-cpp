#pragma once

#include "global_header.h"


class HttpConnection:public std::enable_shared_from_this<HttpConnection>
{
public:
    HttpConnection(tcp::socket socket);
    void Start();

private:
    //tcp不是有超时检测吗，cpp为什么还需要自己实现超时检测
    void CheckDeadline();
    void WriteResponse();
    void HandleReq();

    tcp::socket _socket;
    beast::flat_buffer _buffer{ 8192 };
    http::request<http::dynamic_body> _request;
    http::response<http::dynamic_body> _response;
    net::steady_timer deadline_{
        _socket.get_executor(), std::chrono::seconds(60);
    };

};

