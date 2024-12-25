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
            //为什么不用make_shared(),因为make_shared需要调用当前类的构造函数
            _instance = std::shared_ptr<T>(new T);
            });
        return _instance;
    }

    void PrintAddress() {
        std::cout << _instance.get() << std::endl;
    }

    //确保析构函数是虚函数，不然在用基类指针指向派生类的对象，调用析构时候只会调用基类的析构，不会调用派生类的析构
    virtual ~Singleton() {
        std::cout << "Singleton Deconstructure" << std::endl;
    }
};


/*
    类的静态成员变量，
        如果不是模板类，需要在cpp文件中定义（实例化）
        如果是模板类，就直接在头文件中定义
*/
template <typename T>
std::shared_ptr<T> Singleton<T>::_instance = nullptr;
