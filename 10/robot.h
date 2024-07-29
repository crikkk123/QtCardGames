#ifndef ROBOT_H
#define ROBOT_H

#include <QObject>
#include "player.h"

class Robot : public Player
{
    Q_OBJECT
public:
    using Player::Player;
    explicit Robot(QObject *parent = nullptr);

    virtual void prepareCallLord() override;     // 准备叫地主
    virtual void preparePlayHand() override;     // 准备出牌

    // 考虑叫地主的函数，在RobotGrapLord类里进行调用
    void thinkCallLord();

    void thinkPlayHand();
};

#endif // ROBOT_H
