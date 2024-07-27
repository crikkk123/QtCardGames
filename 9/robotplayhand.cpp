#include "robotplayhand.h"

RobotPlayHand::RobotPlayHand(Robot *player, QObject *parent)
{
    m_player = player;
}

void RobotPlayHand::run()
{
    sleep(2);
    m_player->thinkPlayHand();
}
