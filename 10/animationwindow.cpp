#include "animationwindow.h"

#include <QPainter>
#include <QTimer>

AnimationWindow::AnimationWindow(QWidget *parent)
    : QWidget{parent}
{
    m_planx = 0;
}

void AnimationWindow::showBetScore(int bet)
{
    m_planx = 0;

    if(bet==1)
    {
        m_image.load(":/images/score1.png");
    }
    else if(bet==2)
    {
        m_image.load(":/images/score2.png");
    }
    else if(bet==3)
    {
        m_image.load(":/images/score3.png");
    }
    update();
    QTimer::singleShot(2000,this,&AnimationWindow::hide);
}

void AnimationWindow::showSequence(Type type)
{
    m_planx = 0;

    QString name=type==Pair?":/images/liandui.png":":/images/shunzi.png";
    m_image.load(name);
    update();
    QTimer::singleShot(2000,this,&AnimationWindow::hide);
}

void AnimationWindow::showJokerBomb()
{
    m_index = 0;
    m_planx = 0;
    QTimer* timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,[=](){
        m_index++;
        if(m_index>8)
        {
            timer->stop();
            delete timer;
            m_index = 8;
            hide();
        }
        QString name = QString(":/images/joker_bomb_%1.png").arg(m_index);
        m_image.load(name);
        update();
    });
    timer->start(60);
}

void AnimationWindow::showBomb()
{
    m_index = 0;
    m_planx = 0;
    QTimer* timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,[=](){
        m_index++;
        if(m_index>12)
        {
            timer->stop();
            delete timer;
            m_index = 12;
            hide();
        }
        QString name = QString(":/images/bomb_%1.png").arg(m_index);
        m_image.load(name);
        update();
    });
    timer->start(60);
}

void AnimationWindow::showPlane()
{
    m_planx = width();
    m_image.load(":/images/plane_1.png");
    setFixedHeight(m_image.height());
    update();

    int step = width() / 5;     // 图片有5张
    QTimer* timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,[=](){
        static int dist = 0;
        static int times = 0;
        dist+=5;
        if(dist>=step)
        {
            dist = 0;
            times++;
            QString name = QString(":/images/plane_%1.png").arg(times%5+1);
            m_image.load(name);
        }
        if(m_planx <= -110)
        {
            timer->stop();
            delete timer;
            dist = times = 0;
            hide();
        }
        m_planx-=5;
        update();
    });
    timer->start(15);
}

void AnimationWindow::paintEvent(QPaintEvent *ev)
{
    QPainter p(this);
    p.drawPixmap(m_planx,0,m_image.width(),m_image.height(),m_image);
}
