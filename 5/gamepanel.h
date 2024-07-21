#ifndef GAMEPANEL_H
#define GAMEPANEL_H

#include <CardPanel.h>
#include <QLabel>
#include <QMainWindow>
#include <QMap>
#include "gamecontrol.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GamePanel; }
QT_END_NAMESPACE

class GamePanel : public QMainWindow
{
    Q_OBJECT

public:
    GamePanel(QWidget *parent = nullptr);
    ~GamePanel();

    // 初始化游戏控制类信息
    void gameControlInit();
    // 更新分数面板的分数
    void updatePlayerScore();
    // 切割并存储图片
    void initCardMap();
    // 裁剪图片
    void cropImage(QPixmap& pix,int x,int y,Card& c);
    // 初始化游戏按钮组
    void initButtonsGroup();
    // 初始化玩家在窗口中的上下文环境
    void initPlayerContext();
    // 初始化游戏场景
    void initGameScene();

protected:
    void paintEvent(QPaintEvent* ev);

private:
    enum CardAlign{Horizontal,Vertical};

    struct PlayerContext
    {
        // 1、玩家扑克牌显示的区域
        QRect cardRect;
        // 2、出牌的区域
        QRect playHandRect;
        // 3、扑克牌的对齐方式  水平或者垂直
        CardAlign align;
        // 4、扑克牌显示正面还是背面
        bool isFrontSide;
        // 5、游戏过程中的提示信息，比如：不出
        QLabel* info;
        // 6、玩家的头像
        QLabel* roleImg;
        // 7、玩家刚打出的牌
        Cards lastCards;
    };

    Ui::GamePanel *ui;
    QPixmap m_bkImage;  // 背景图片
    GameControl* m_gameCtl;
    QVector<Player*> m_playerList;

    QMap<Card,CardPanel*> m_cardMap;
    QSize m_cardSize;
    QPixmap m_cardBackImg;
    QMap<Player*,PlayerContext> m_contextMap;
    CardPanel* m_baseCard;
    CardPanel* m_moveCard;
    QVector<CardPanel*> m_last3Card;
};
#endif // GAMEPANEL_H
