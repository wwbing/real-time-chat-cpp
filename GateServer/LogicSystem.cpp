#include "LogicSystem.h"
#include "HttpConnection.h"

LogicSystem::LogicSystem()
{
    RegGet(
        "/get_test",
        [](std::shared_ptr<HttpConnection> connection) -> void{
            beast::ostream(connection->_response.body())<<"receive get_test request";
        }
    );
}

LogicSystem::~LogicSystem() {

}

//
bool LogicSystem::HandleGet(std::string url, std::shared_ptr<HttpConnection> connection)
{
    if (_get_handlers.find(url) == _get_handlers.end()) {
        return false;
    }

    _get_handlers[url](connection);

    return true;
}

//注册url和对应的get处理函数
void LogicSystem::RegGet(std::string url, HttpHandler get_handler) {
    _get_handlers.insert(make_pair(url, get_handler));
}

