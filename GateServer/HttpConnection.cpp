#include "HttpConnection.h"
#include "LogicSystem.h"

HttpConnection::HttpConnection(tcp::socket socket):
    _socket(std::move(socket))

{

}

void HttpConnection::Start() {
    auto self = shared_from_this(); //延长生命周期，避免回调期间崩溃

    //异步读取request请求
    http::async_read(
        _socket,
        _buffer,
        _request,

        [self](beast::error_code ec, std::size_t bytes_transfer) {
            try {
                if (ec) {
                    std::cout << "http sever read from client err ,err is : " << ec.what() << std::endl;
                    return;
                }

                boost::ignore_unused(bytes_transfer);
                self->HandleReq();
                self->CheckDeadline();
            }
            catch (std::exception& e) {
                std::cout << "exception is: " << e.what() << std::endl;
            }
        }
    );
}

//解析request和回应
void HttpConnection::HandleReq() {

    //设置回应的版本
    _response.version(_request.version());

    _response.keep_alive(false);

    //只处理get请求,暂时不管post
    if (_request.method() == http::verb::get) {

        //交给逻辑系统类处理
        bool success = LogicSystem::GetInstance()->HandleGet(_request.target(), shared_from_this());
        
        if (!success) {         //没成功的情况下，写好错误信息返回客户端
            _response.result(http::status::not_found);
            _response.set(http::field::content_type, "text/plain");
            beast::ostream(_response.body()) << "url not found\r\n";
            WriteResponse();
            return;
        }       
        else {                  //成功,将LogicSystem处理后写好的正确信息返回客户端
            _response.result(http::status::ok);
            _response.set(http::field::server, "GateServer");   //补充回复方的信息
            WriteResponse();
            return;
        }
    }
}


//定时器
void HttpConnection::CheckDeadline() {
    auto self = shared_from_this();

    deadline_.async_wait(
        [self](beast::error_code ec) {

            if (!ec) {              //定时器超时就把socket关了
                self->_socket.close();
            }
        }
    );
}


//回应时候具体的写操作
void HttpConnection::WriteResponse(){
    auto self = shared_from_this();

    _response.content_length(_response.body().size());

    http::async_write(
        _socket,
        _response,

        [self](beast::error_code ec, std::size_t bytes_transfer)
        {

            self->_socket.shutdown(tcp::socket::shutdown_send, ec);
            self->deadline_.cancel();

        }
    );

}