#ifndef CHATITEMBASE_H
#define CHATITEMBASE_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include "global.h"
class BubbleFrame;

//该类是聊天界面每一条发送信息，主要实现每一条消息内部布局
class ChatItemBase : public QWidget
{
    Q_OBJECT
public:
    explicit ChatItemBase(ChatRole role, QWidget *parent = nullptr);
    void setUserName(const QString &name);
    void setUserIcon(const QPixmap &icon);
    void setWidget(QWidget *w);

private:
    ChatRole    m_role;
    QLabel      *m_pNameLabel;
    QLabel      *m_pIconLabel;
    QWidget     *m_pBubble;
};

#endif // CHATITEMBASE_H
