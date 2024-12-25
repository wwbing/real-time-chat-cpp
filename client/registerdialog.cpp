#include "registerdialog.h"
#include "ui_registerdialog.h"
#include "global.h"
#include "httpmgr.h"

RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    initHttpHandlers();

    //设置输入密码的line_edit的输入模式是密码模式，这样输入就看不到具体显示了
    ui->pass_edit->setEchoMode(QLineEdit::Password);
    ui->confirm_edit->setEchoMode(QLineEdit::Password);

    //刷新的逻辑
    ui->err_tip->setProperty("state","normal"); //设置err_tip初始状态为normal
    repolish(ui->err_tip);

    connect(ui->get_code, &QPushButton::clicked, this, &RegisterDialog::get_code_click);
    connect(HttpMgr::GetInstance().get(), &HttpMgr::sig_reg_mod_finish, this, &RegisterDialog::slot_reg_mod_finish);
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

//验证码点击槽函数
void RegisterDialog::get_code_click(){

    //获取文本并且和正则表达式判断
    auto email = ui->email_edit->text();
    QRegularExpression regex(R"((^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$))");
    bool match = regex.match(email).hasMatch();
    if(match){
        //发送http验证码
        QJsonObject json_obj;
        json_obj["email"] = email;

        HttpMgr::GetInstance()->PostHttpReq(
                                            QUrl(gate_url_prefix+"/get_varifycode"),
                                            json_obj,
                                            ReqId::ID_GET_VERIFT_CODE,
                                            Modules::REGISERMOD
                                            );
    }
    else{
        showTip("邮箱格式错误", match);
    }
}

void RegisterDialog::showTip(const QString& str, const bool is_ok)const{

    ui->err_tip->setText(str);
    if(is_ok){
        ui->err_tip->setProperty("state", "normal");
    }
    else{
        ui->err_tip->setProperty("state", "err");
    }
    repolish(ui->err_tip);
}

//注册模块处理http请求结束信号槽函数
void RegisterDialog::slot_reg_mod_finish(ReqId id, QString res, ErrorCodes err){
    if(err != ErrorCodes::SUCCESS){
        showTip("网络请求错误", false);
        return;
    }
    else{
        //解析json字符串，res转换为QByteArray
        QJsonDocument jsonDoc = QJsonDocument::fromJson(res.toUtf8());
        if(jsonDoc.isNull()){
            showTip("json解析失败",false);
        }
        else if(!jsonDoc.isObject()){
            showTip("解析解析错误",false);
            return;
        }
        else{
            //解析成功，传递给回调函数处理
            _handlers[id](jsonDoc.object());
            return;
        }
    }
}

void RegisterDialog::initHttpHandlers()
{
    //注册验证码回包的逻辑
    _handlers.insert(ReqId::ID_GET_VERIFT_CODE, [this](const QJsonObject& jsonObj)->void{
        int error = jsonObj["error"].toInt();

        if(error != ErrorCodes::SUCCESS){
            showTip("参数错误", false);
            return;
        }

        auto email = jsonObj["email"].toString();
        showTip("验证码已经发送到邮箱，注意查收", true);
        qDebug()<<"email is: "<<email;

    });
}


