#pragma once
#include<iostream>

template <typename T>

class Singleton {
protected:
    Singleton() = default;
    Singleton(const Singleton<T>&) = delete;
    Singleton& operator=(const Singleton<T>&) = delete;

    static std::shared_ptr<T> _instance;

public:
    static std::shared_ptr<T> GetInstance() {
        static std::once_flag s_flag;

        std::call_once(s_flag, [&]() {
            //Ϊʲô����make_shared(),��Ϊmake_shared��Ҫ���õ�ǰ��Ĺ��캯��
            _instance = std::shared_ptr<T>(new T);
            });
        return _instance;
    }

    void PrintAddress() {
        std::cout << _instance.get() << std::endl;
    }

    //ȷ�������������麯������Ȼ���û���ָ��ָ��������Ķ��󣬵�������ʱ��ֻ����û����������������������������
    virtual ~Singleton() {
        std::cout << "Singleton Deconstructure" << std::endl;
    }
};


/*
    ��ľ�̬��Ա������
        �������ģ���࣬��Ҫ��cpp�ļ��ж��壨ʵ������
        �����ģ���࣬��ֱ����ͷ�ļ��ж���
*/
template <typename T>
std::shared_ptr<T> Singleton<T>::_instance = nullptr;