#ifndef FINDSUCCESSDLG_H
#define FINDSUCCESSDLG_H

#include <QDialog>
#include <memory>
#include "userdata.h"
namespace Ui {
class FindSuccessDlg;
}

//搜索用户后，如果用户不是自己的好友就加好友
//该类是加好友对话框
class FindSuccessDlg : public QDialog
{
    Q_OBJECT

public:
    explicit FindSuccessDlg(QWidget *parent = nullptr);
    ~FindSuccessDlg();
    void SetSearchInfo(std::shared_ptr<SearchInfo> si);
private slots:
    void on_add_friend_btn_clicked();

private:
    Ui::FindSuccessDlg *ui;
    QWidget * _parent;
    std::shared_ptr<SearchInfo> _si;
};

#endif // FINDSUCCESSDLG_H
