#pragma once
#include <vector>
#include <boost/asio.hpp>
#include "Singleton.h"

/*
	���ASIO IOContext Pool �ṹ���ö��iocontext���ڲ�ͬ���߳���
*/

class AsioIOServicePool:public Singleton<AsioIOServicePool>
{
	friend Singleton<AsioIOServicePool>;
public:
	using IOService = boost::asio::io_context;
	using Work = boost::asio::io_context::work;	
	/*
	*	���������:io_context run������ʼ�����Ƿ������ģ����û���¼��������Ϸ��أ�
	��	��work��װһ���ʹ��������û���¼���������һֱ�ȣ�һֱ����
		����ײ����ʵ����Ҫ��Դ��
	*/
	using WorkPtr = std::unique_ptr<Work>;

	~AsioIOServicePool();
	AsioIOServicePool(const AsioIOServicePool&) = delete;
	AsioIOServicePool& operator=(const AsioIOServicePool&) = delete;

	// ʹ�� round-robin �ķ�ʽ����һ�� io_service
	boost::asio::io_context& GetIOService();
	void Stop();

private:
	AsioIOServicePool(std::size_t size = 2/*std::thread::hardware_concurrency()*/);
	std::vector<IOService>		_ioServices;
	std::vector<WorkPtr>		_works;
	std::vector<std::thread>	_threads;
	std::size_t					_nextIOService;
};

