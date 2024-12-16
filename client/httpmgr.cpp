#include "httpmgr.h"

HttpMgr::HttpMgr()
{
    QObject::connect(this, &HttpMgr::sig_http_finish, this, &HttpMgr::slot_http_finish);
}

HttpMgr::~HttpMgr()
{

}

void HttpMgr::PostHttpReq(QUrl url, QJsonObject json, ReqId req_id, Modules mod)
{
    QByteArray data = QJsonDocument(json).toJson(); //将json转成字节数组

    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(data.length()));

    auto self = shared_from_this(); //下来深入了解

    QNetworkReply* reply = _manager.post(request, data); //发送带数据的请求并获得回复数据

    QObject::connect(reply, &QNetworkReply::finished, this, [self, reply, req_id, mod](){
        //处理错误
        if(reply->error() != QNetworkReply::NoError){
            qDebug()<<reply->errorString();

            //发送信号通知完成
            emit self->sig_http_finish(req_id, " ", ErrorCodes::ERR_NETWORK, mod);
            reply->deleteLater();   //告诉qt等下帮我们回收，避免reply可能还会使用而不存在
            return;
        }
        //无错误
        else{
            QString res = QString::fromUtf8(reply->readAll());

            //发送信号通知完成
            emit self->sig_http_finish(req_id, res, ErrorCodes::SUCCESS, mod);
            reply->deleteLater();
            return;
        }
    });

}

void HttpMgr::slot_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod)
{
    if(mod == Modules::REGISERMOD){
        //发送信号给指定模块：http响应结束了
        emit sig_reg_mod_finish(id, res, err);
    }
}
