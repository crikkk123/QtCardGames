#ifndef BUTTONGROUP_H
#define BUTTONGROUP_H

#include <QWidget>

namespace Ui {
class ButtonGroup;
}

class ButtonGroup : public QWidget
{
    Q_OBJECT

public:
        //     开始    出牌     不要/出牌   叫地主    什么也不显示
    enum Panel{Start,PlayCard,PassOrPlay,CallLord,Empty};
    explicit ButtonGroup(QWidget *parent = nullptr);
    ~ButtonGroup();

    // 初始化按钮  各种按钮，开始游戏、叫地主、出牌不出
    void initButtons();
    // 处理page页的切换，当机器玩家叫了一分后，游戏玩家一分按钮将不显示
    void selectPanel(Panel type,int bet=0);

signals:
    // 发射信号在GamePanel中处理  在initButtonsGroup函数中处理
    // 开始游戏
    void startGame();
    // 出牌
    void playHand();
    // 不出牌
    void pass();
    // 抢地主
    void betPoint(int bet);

private:
    Ui::ButtonGroup *ui;
};

#endif // BUTTONGROUP_H
