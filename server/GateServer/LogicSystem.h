#pragma once
#include "Singleton.h"
#include <functional>
#include <map>
#include "const.h"

class HttpConnection;
typedef std::function<void(std::shared_ptr<HttpConnection>)> HttpHandler;

/*
	LogicSystem��ʵ�ֶ�HttpConnection���ȡ���Ŀͻ��˵�����
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
	
	//post�����get����Ļص�����map��keyΪurl��valueΪ�ص�������
	std::map<std::string, HttpHandler> _post_handlers;
	std::map<std::string, HttpHandler> _get_handlers;
};

