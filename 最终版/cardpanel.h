#ifndef CARDPANEL_H
#define CARDPANEL_H

#include "card.h"
#include "player.h"

#include <QWidget>

class CardPanel : public QWidget
{
    Q_OBJECT
public:
    explicit CardPanel(QWidget *parent = nullptr);

    // 设置获取图片函数
    void setImage(const QPixmap& front,const QPixmap& back);      // 显示的有正面和背面  其他玩家或者自己的牌的正反面
    QPixmap getImage();        // 获取牌的是正面还是背面

    // 扑克牌显示那一面
    void setFrontSide(bool flag);       // 设置牌的正反面
    bool isFrontSide();                 // 是否是正面

    // 记录窗口是否被选中   扑克牌被选中是有一个上升的画面的  出牌的时候
    void setSelected(bool flag);        // 设置窗口是否被选中
    bool isSelected();

    // 扑克牌的花色以及点数
    void setCard(const Card &card);
    Card getCard();

    // 扑克牌的所有者  三个人中的一个
    void setOwner(Player* player);
    Player* getOwner();

    // 模拟扑克牌点击事件
    void clicked();

protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);
signals:
    void cardSelected(Qt::MouseButton button);

private:
    QPixmap m_front;
    QPixmap m_back;

    bool m_isfront = true;
    bool m_isSelect = false;

    Card m_card;

    Player* m_owner = nullptr;
};

#endif // CARDPANEL_H
