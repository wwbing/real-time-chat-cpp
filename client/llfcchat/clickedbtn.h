#ifndef CLICKEDBTN_H
#define CLICKEDBTN_H
#include <QPushButton>

//该类实现按钮的点击效果，包括普通状态，悬浮状态，以及按下状态
class ClickedBtn:public QPushButton
{
    Q_OBJECT
public:
    ClickedBtn(QWidget *parent = nullptr);
    ~ClickedBtn();
    void SetState(QString nomal, QString hover, QString press);
protected:
    virtual void enterEvent(QEvent *event) override; // 鼠标进入
    virtual void leaveEvent(QEvent *event) override; // 鼠标离开
    virtual void mousePressEvent(QMouseEvent *event) override; // 鼠标按下
    virtual void mouseReleaseEvent(QMouseEvent *event) override; // 鼠标释放
private:
    QString _normal;
    QString _hover;
    QString _press;
};

#endif // CLICKEDBTN_H
