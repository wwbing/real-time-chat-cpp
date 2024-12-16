#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

/***********************************************
*
* @file      logindialog.h
*
* @brief     LoginDialog登陆界面
*
* @author    jiahao
*
* @data      2024/12/15
*
***********************************************/

#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private:
    Ui::LoginDialog *ui;

signals:
    void switchRegister();
};

#endif // LOGINDIALOG_H
