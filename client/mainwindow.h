#ifndef MAINWINDOW_H
#define MAINWINDOW_H
/***********************************************
*
* @file      mainwindow.h
*
* @brief     MainWindow主界面
*
* @author    jiahao
*
* @data      2024/12/13
*
***********************************************/

#include <QMainWindow>
#include "logindialog.h"
#include "registerdialog.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void SlotSwitchReg();


private:
    Ui::MainWindow *ui;
    LoginDialog*    _login_dlg;
    RegisterDialog* _reg_dlg;
};
#endif // MAINWINDOW_H
