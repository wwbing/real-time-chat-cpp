#include "CServer.h"

CServer::CServer(boost::asio::io_context& ioc, unsigned short& port):
    _ioc(ioc),
    _acceptor(ioc, tcp::endpoint(tcp::v4(), port)),
    _socket(ioc){

}

void CServer::Start() {
    auto self = shared_from_this();
    _acceptor.async_accept(_socket, [self](beast::error_code ec) {
        try {
            //������������ǰ���ӣ�ȥ������������
            if (ec) {
                self->Start();
                return;
            }
            else {
                //���������ӣ�������HttpConnection���������
                std::make_shared<HttpConnection>(std::move(_socket))->Start();

                //��������
                self->Start();
            }

            

        }
        catch (std::exception& exp) {

        }

        });
}