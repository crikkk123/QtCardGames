#include "cardpanel.h"
#include <QMouseEvent>
#include <QPainter>

CardPanel::CardPanel(QWidget *parent) : QWidget(parent)
{

}

void CardPanel::setImage(const QPixmap& front,const QPixmap& back)
{
    m_front = front;
    m_back = back;

    setFixedSize(m_front.size());

    update();       // 这块需要重新绘制，调用update后，paintEvent就被框架调用了
}

QPixmap CardPanel::getImage(){
    return m_front;
}

void CardPanel::setFrontSide(bool flag)
{
    m_isfront = flag;
}

bool CardPanel::isFrontSide()
{
    return m_isfront;
}

void CardPanel::setSelected(bool flag)
{
    m_isSelect = flag;
}

bool CardPanel::isSelected()
{
    return m_isSelect;
}

void CardPanel::setCard(const Card &card)
{
    m_card = card;
}

Card CardPanel::getCard()
{
    return m_card;
}

void CardPanel::setOwner(Player *player)
{
    m_owner = player;
}

Player *CardPanel::getOwner()
{
    return m_owner;
}

void CardPanel::clicked()
{
    emit cardSelected(Qt::LeftButton);
}

void CardPanel::paintEvent(QPaintEvent* event){
    QPainter p(this);     // Qt中的画家的一个类
    if(m_isfront)
    {
        // rect() 整个窗口或小部件的区域
        p.drawPixmap(rect(),m_front);   // 绘制前面
    }
    else
    {
        p.drawPixmap(rect(),m_back);    // 绘制背面
    }
}

void CardPanel::mousePressEvent(QMouseEvent *event)
{
    emit cardSelected(event->button());
}
