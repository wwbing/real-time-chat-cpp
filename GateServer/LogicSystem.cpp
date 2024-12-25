#include "LogicSystem.h"
#include "HttpConnection.h"
#include "VerifyGrpcClient.h"

LogicSystem::LogicSystem()
{
    RegGet(
        "/get_test",
        [](std::shared_ptr<HttpConnection> connection) -> void{
            beast::ostream(connection->_response.body()) << "receive get_test request" << std::endl;

            int i = 0;
            for (auto& elem : connection->_get_params) {
                i++;
                beast::ostream(connection->_response.body()) << "param" << i << " key is " << elem.first;
                beast::ostream(connection->_response.body()) << ", " << " value is " << elem.second << std::endl;
            }

        }
    );

    RegPost(
        "/get_varifycode",
        [](std::shared_ptr<HttpConnection> connection) -> void{
            auto body_string = boost::beast::buffers_to_string(connection->_request.body().data());
            std::cout << "receive body is: " << body_string << std::endl;
            connection->_response.set(http::field::content_type, "text/json");

            Json::Value root;
            Json::Reader reader;
            Json::Value src_root;

            bool parse_success = reader.parse(body_string, src_root);

            //解析失败
            if (!parse_success) {
                std::cout << "Failed to parse JSON data!" << std::endl;
                beast::ostream(connection->_response.body()) << "Failed to parse JSON data!" << std::endl;
                return;
            }

            //没有email的字段
            if (!src_root.isMember("email")) {   
                std::cout << "There is no JSON data!" << std::endl;
                beast::ostream(connection->_response.body()) << "There is no JSON data!" << std::endl;
                return;
            }

            auto email = src_root["email"].asString();
            //给验证服务发送grpc请求
            GetVarifyRsp rsp = VerifyGrpcClient::GetInstance()->GetVerifyCode(email);

            std::cout << "send back email is " << email << std::endl;
            root["error"] = rsp.error();
            root["email"] = src_root["email"];
            std::string jsonstr = root.toStyledString();
            beast::ostream(connection->_response.body()) << jsonstr;
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

//
bool LogicSystem::HandlePost(std::string url, std::shared_ptr<HttpConnection> connection)
{
    if (_post_handlers.find(url) == _post_handlers.end()) {
        return false;
    }

    _post_handlers[url](connection);

    return true;
}


//注册url和对应的post处理函数
void LogicSystem::RegPost(std::string url, HttpHandler post_handler) {
    _post_handlers.insert(make_pair(url, post_handler));
}
