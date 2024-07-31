#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include "cards.h"

class Player : public QObject
{
    Q_OBJECT
public:
    // 角色 地主 农民
    enum Role{Lord,Farmer,};

    // 性别  男  女
    enum Sex{Man,Woman,};

    // 头像的显示方向  左   右
    enum Direction{Left,Right,};

    // 玩家的类型 机器人、玩家、Unkown
    enum Type{Robot,User,Unkown,};

    explicit Player(QObject *parent = nullptr);
    explicit Player(QString name,QObject *parent = nullptr);

    // 名字
    void setName(QString name);
    QString getName();

    // 角色
    void setRole(Role role);
    Role getRole();

    // 性别
    void setSex(Sex sex);
    Sex getSex();

    // 头像显示方向
    void setDirection(Direction direction);
    Direction getDirection();

    // 玩家类型
    void setType(Type type);
    Type getType();

    // 玩家的分数
    void setScore(int score);
    int getScore();

    // 游戏结果
    void setWin(bool flag);
    bool isWin();

    // 当前对象的上家，下家
    void setPrevPlayer(Player* player);
    void setNextPlayer(Player* player);
    Player* getPrevPlayer();
    Player* getNextPlayer();

    // 叫地主/抢地主
    void grabLordBet(int point);

    // 存储扑克牌（发牌的时候得到的）
    void storeDispatchCard(const Card& card);
    void storeDispatchCard(const Cards& cards);   // 最后三张底牌是一起发到玩家手中

    // 获取玩家手中的牌
    Cards getCards();
    // 清空玩家手中的牌
    void clearCards();

    // 出牌
    void playHand(Cards& cards);

    // 设置出牌的玩家已经待处理的扑克牌
    void setPendingInfo(Player* player,const Cards &cards);
    Player* getPendPlayer();
    Cards getPendCards();

    // 存储出牌玩家对象和打出的牌
    void storePendingInfo(Player* player, const Cards &cards);

    // 虚函数
    virtual void prepareCallLord();     // 准备叫地主
    virtual void preparePlayHand();     // 准备出牌

signals:
    // 通知已经叫地主下注了
    void notifyGrabLordBet(Player* player,int bet);
    // 通知已经出牌
    void notifyPlayHand(Player* player,Cards& cards);
    // 通知已经发牌了
    void notifyPickCards(Player* player,const Cards& cards);

protected:
    QString m_name;
    Role m_role;
    Sex m_sex;
    Direction m_direction;
    Type m_type;

    int m_score = 0;
    bool m_isWin = false;

    Player* m_prev = nullptr;
    Player* m_next = nullptr;

    Cards m_cards;   // 储存多张扑克牌（玩家手中的牌）
    Cards m_pendCards;  // 出去的牌别人是否要
    Player* m_pendPlayer = nullptr;   // 判断这个牌是不是自己出的，如果是则可以出自由牌
};

#endif // PLAYER_H
