#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //这里的this参数指定他的父窗口是当前的窗口mainwindow，这样不用手动回收这两个窗口指针(对象树)
    _login_dlg = new LoginDialog(this);
    setCentralWidget(_login_dlg);

    _reg_dlg = new RegisterDialog(this);

    //创建和注册信号和槽
    connect(_login_dlg, &LoginDialog::switchRegister, this, &MainWindow::SlotSwitchReg);

    //登录窗口嵌入到主窗口中
    _login_dlg->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    _reg_dlg->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    _reg_dlg->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//切换到注册界面
void MainWindow::SlotSwitchReg()
{
    setCentralWidget(_reg_dlg);
    _login_dlg->hide();
    _reg_dlg->show();
}

