#pragma once
#include "Singleton.h"
#include <functional>
#include <map>
#include "const.h"

class HttpConnection;
typedef std::function<void(std::shared_ptr<HttpConnection>)> HttpHandler;

/*
	LogicSystem类实现对HttpConnection类读取到的客户端的内容
*/
class LogicSystem :public Singleton<LogicSystem>
{
	friend class Singleton<LogicSystem>;
public:
	~LogicSystem();
	bool HandleGet(std::string, std::shared_ptr<HttpConnection>);
	void RegGet(std::string, HttpHandler handler);

	bool HandlePost(std::string, std::shared_ptr<HttpConnection>);
	void RegPost(std::string, HttpHandler handler);
	
private:
	LogicSystem();
	
	//post请求和get请求的回调函数map。key为url，value为回调函数。
	std::map<std::string, HttpHandler> _post_handlers;
	std::map<std::string, HttpHandler> _get_handlers;
};

