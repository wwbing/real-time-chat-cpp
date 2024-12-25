#include "mainwindow.h"

#include <global.h>
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //加载qss文件，:/表示rc.qrc下的文件
    QFile qss(":/style/stylesheet.qss");

    if(qss.open(QFile::ReadOnly)){
        qDebug("Open qss file success");
        QString style = QString::fromUtf8(qss.readAll());
        a.setStyleSheet(style);
        qss.close();
    }
    else{
        qDebug("Open qss file failed");
    }

    QString fileName = "config.ini";
    QString app_path = QCoreApplication::applicationDirPath();
    QString config_path = QDir::toNativeSeparators(app_path + QDir::separator() + fileName);

    QSettings setting(config_path, QSettings::IniFormat);
    QString gate_host = setting.value("GateServer/host").toString();
    QString gate_port = setting.value("GateServer/port").toString();
    gate_url_prefix = "http://"+gate_host+":"+gate_port;

    MainWindow w;
    w.show();
    return a.exec();
}
