#ifndef CHATPAGE_H
#define CHATPAGE_H

#include <QWidget>
#include "userdata.h"
#include <QMap>

namespace Ui {
class ChatPage;
}

/*
 *  ChatDialog在发消息（右侧）的界面使用的stackWidget实现，stackWidget可以切换为不同的page
 *  比如ChatPage和friend_apply_page和friend_info_page
 *
 *  该类是ChatPage的实现，主要包括了聊天记录显示部分和消息编辑发送部分
*/

class ChatPage : public QWidget
{
    Q_OBJECT
public:
    explicit ChatPage(QWidget *parent = nullptr);
    ~ChatPage();
    void SetUserInfo(std::shared_ptr<UserInfo> user_info);
    void AppendChatMsg(std::shared_ptr<TextChatData> msg);

protected:
    void paintEvent(QPaintEvent *event);

private:
    void clearItems();
    Ui::ChatPage *ui;
    std::shared_ptr<UserInfo> _user_info;
    QMap<QString, QWidget*>   _bubble_map;

signals:
    void sig_append_send_chat_msg(std::shared_ptr<TextChatData> msg);

private slots:
    void on_send_btn_clicked();
    void on_receive_btn_clicked();
};

#endif // CHATPAGE_H
