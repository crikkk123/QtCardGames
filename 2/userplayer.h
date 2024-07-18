#ifndef USERPLAYER_H
#define USERPLAYER_H

#include <QObject>
#include "player.h"

class UserPlayer : public Player
{
    Q_OBJECT
public:
    using Player::Player;
    explicit UserPlayer(QObject *parent = nullptr);

    virtual void prepareCallLord() override;     // 准备叫地主
    virtual void preparePlayHand() override;     // 准备出牌
};

#endif // USERPLAYER_H
