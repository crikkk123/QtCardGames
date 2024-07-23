#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include <QObject>
#include "robot.h"
#include "userplayer.h"
#include "cards.h"

struct BetRecord
{
    BetRecord()
    {

    }

    void reset()
    {
        player=nullptr;
        bet=0;
        times=0;
    }
    Player* player;
    int bet;
    int times;  // 第几次叫地主
};

class GameControl : public QObject
{
    Q_OBJECT
public:
    // 游戏状态  发牌、叫地主、出牌  机器人玩家需要知道这个状态
    enum GameStatus
    {
        DispatchCard,
        CallingLord,
        PlayingHand,
    };

    // 玩家状态  叫地主、出牌、胜利
    enum PlayerStatus
    {
        ThinkingForCallLord,
        ThinkingForPlayHand,
        Winning,
    };

    explicit GameControl(QObject *parent = nullptr);

    // 初始化玩家
    void playerInit();

    // 得到玩家的实例对象
    Robot* getLeftRobot();
    Robot* getRightRobot();
    UserPlayer* getUserPlayer();

    void setCurrentPlayer(Player* player);
    Player* getCurrentPlayer();

    // 得到出牌玩家和打出的牌  pend未处理的
    Player* getPendPlayer();
    Cards getPendCards();

    // 初始化扑克牌
    void initAllCards();
    // 每次发一张牌  随机抽取一张
    Card takeOneCard();
    // 得到最后的三张底牌
    Cards getSurplusCards();
    // 重置卡牌数据 游戏结束了洗牌
    void resetCardData();

    // 准备叫地主
    void startLordCard();
    // 成为地主
    void becomeLord(Player* player);
    // 清空所有玩家的得分
    void clearPlayerScore();

    // 得到玩家下注的最高分数
    int getPlayerMaxBet();
    // 处理叫地主
    void onGrabBet(Player* player,int bet);
    // 处理出牌

signals:
    void playerStatusChanged(Player* player,PlayerStatus status);
    // 通知玩家抢地主了
    void notifyGrabLordBet(Player* player,int bet,bool flag);
    // 游戏状态发送变化
    void gameStatusChanged(GameStatus status);

private:
    Robot* m_robotLeft;
    Robot* m_robotRight;
    UserPlayer* m_user;
    Player* m_currPlayer;     // 指定当前玩家

    Cards m_pendCards;       // 玩家出的牌
    Player* m_pendPlayer;    // 出牌的玩家

    Cards m_allCards;       // 初始化的牌   52张+大小王
    BetRecord m_betRecord;
};

#endif // GAMECONTROL_H
