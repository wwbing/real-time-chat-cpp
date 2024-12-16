#ifndef HTTPMGR_H
#define HTTPMGR_H

/***********************************************
*
* @file      httpmgr.h
*
* @brief     HttpManeger 管理类（单例）, 继承单例的基类
*
* @author    jiahao
*
* @data      2024/12/15
*
***********************************************/

#include "singleton.h"
#include <QUrl>
#include <QString>
#include <QNetworkAccessManager>    //tcp udp等网络模块
#include <QObject>                  //使用信号和槽功能
#include <QJsonObject>              //信息包装成json
#include <QJsonDocument>            //解析json

//CRTP:奇异递归模板
class HttpMgr : public QObject, public Singleton<HttpMgr>, public std::enable_shared_from_this<HttpMgr>
{
    Q_OBJECT        //继承了QObject，还需要声明这个宏才能使用信号和槽
public:
    ~HttpMgr();

private:
    HttpMgr();
    friend class Singleton<HttpMgr>; //将其声明为友元，在基类的构造_instance实例的时候能够调用当前类的私有构造函数
    QNetworkAccessManager _manager;

    void PostHttpReq(QUrl url, QJsonObject json, ReqId req_id, Modules mod); //发送http请求

private slots:
    void slot_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod); //处理信号的槽函数参数要和信号匹配,可少不可多

signals:
    void sig_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod); //信号携带数据一起发送
    void sig_reg_mod_finish(ReqId id, QString res, ErrorCodes err);
};

#endif // HTTPMGR_H
