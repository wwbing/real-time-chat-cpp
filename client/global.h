#ifndef GLOBAL_H
#define GLOBAL_H
/***********************************************
*
* @file      global.h
*
* @brief     全局头文件,repolish用来刷新组件qss,各种枚举类型数据
*
* @author    jiahao
*
* @data      2024/12/15
*
***********************************************/


#include <QWidget>
#include <functional>
#include <QRegularExpression>
#include <QByteArray>
#include <QNetworkReply>

#include <memory>
#include <mutex>
#include <iostream>
#include <QJsonObject>
#include <QDir>
#include <QSettings>

#include "QStyle"


//repolish：用来刷新qss
extern std::function<void(QWidget*)> repolish;

enum ReqId{
    ID_GET_VERIFT_CODE = 1001,      //获取验证码
    ID_REG_USER = 1001,             //注册用户
};

enum Modules{
    REGISERMOD = 0,                 //注册模块
};

enum ErrorCodes{
    SUCCESS = 0,
    ERR_JSON = 1,                   //json解析失败
    ERR_NETWORK = 2,                //网络错误
};

extern QString gate_url_prefix;

#endif // GLOBAL_H
