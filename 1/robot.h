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
};

#endif // ROBOT_H
