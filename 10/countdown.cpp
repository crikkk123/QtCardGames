#include "countdown.h"

#include <QPainter>

CountDown::CountDown(QWidget *parent)
    : QWidget{parent}
{
    setFixedSize(m_clock.size());
    m_timer = new QTimer(this);
    connect(m_timer,&QTimer::timeout,this,[=](){
        m_count--;
        if(m_count<10 && m_count>0)
        {
            m_clock.load(":/images/clock.png");
            m_number = QPixmap(":/images/number.png").copy(m_count*(30+10),0,30,42).scaled(20,30);
            if(m_count==5)
            {
                emit notMuchTime();
            }
        }
        else if(m_count<=0)
        {
            m_clock = QPixmap();
            m_number = QPixmap();
            m_timer->stop();
            emit Cardtimeout();
        }
        update();
    });
}

void CountDown::showCountDowm()
{
    m_count = 15;
    m_timer->start(1000);
}

void CountDown::stopCountDown()
{
    m_timer->stop();
    m_clock = QPixmap();
    m_number = QPixmap();
    update();
}

void CountDown::panintEvent(QPaintEvent *ev)
{
    QPainter p(this);
    p.drawPixmap(rect(),m_clock);
    p.drawPixmap(24,24,m_number.width(),m_number.height(),m_number);
}