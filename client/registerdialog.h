#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

/***********************************************
*
* @file      registerdialog.h
*
* @brief     RegisterDialog注册界面
*
* @author    jiahao
*
* @data      2024/12/15
*
***********************************************/

#include <QDialog>
#include "global.h"

namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = nullptr);
    ~RegisterDialog();

private:
    Ui::RegisterDialog *ui;
    void showTip(const QString& str, const bool is_ok) const;

    void initHttpHandlers();
    QMap<ReqId, std::function<void(const QJsonObject&)>> _handlers;


private slots:
    void get_code_click();      //验证码点击槽函数
    void slot_reg_mod_finish(ReqId id, QString res, ErrorCodes err);
};

#endif // REGISTERDIALOG_H
