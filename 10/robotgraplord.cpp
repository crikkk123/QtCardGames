#include "robotgraplord.h"

RobotGrapLord::RobotGrapLord(Robot* player,QObject *parent)
    : QThread{parent}
{
    m_player = player;
}

void RobotGrapLord::run()
{
    msleep(2000);
    m_player->thinkCallLord();
}
