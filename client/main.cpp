#include "mainwindow.h"

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


    MainWindow w;
    w.show();
    return a.exec();
}
