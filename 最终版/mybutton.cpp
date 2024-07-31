#include "mybutton.h"
#include <QMouseEvent>
#include <QPainter>


MyButton::MyButton(QWidget* parent)
    : QPushButton(parent)
{

}


void MyButton::setImage(QString normal, QString hover, QString pressed)
{
    m_normal = normal;
    m_hover = hover;
    m_pressed = pressed;

    m_pixmap.load(m_normal);      // 开始游戏、叫地主、出牌的按钮的状态
    update();
}

void MyButton::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton)    // 鼠标左键
    {
        m_pixmap.load(m_pressed);
        update();
    }
    // 如果没有这一行，可能自定义按钮和预期不一样
    QPushButton::mousePressEvent(ev);       // 发送信号clicked()
}

void MyButton::mouseReleaseEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton)
    {
        m_pixmap.load(m_normal);
        update();
    }
    QPushButton::mouseReleaseEvent(ev);
}

void MyButton::enterEvent(QEvent *ev)
{
    m_pixmap.load(m_hover);
    update();
}

void MyButton::leaveEvent(QEvent *ev)
{
    m_pixmap.load(m_normal);
    update();
}

void MyButton::paintEvent(QPaintEvent *ev)
{
    QPainter p(this);
    p.drawPixmap(rect(),m_pixmap);
}
