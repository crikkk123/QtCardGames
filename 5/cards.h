#ifndef CARDS_H
#define CARDS_H

#include "card.h"
#include <QSet>
class Cards
{
public:
    enum SortType
    {
        Asc,    // 升序
        Desc,   // 降序
        NoSort  // 不排序
    };

    Cards();

    // 添加扑克牌
    void add(const Card& card); // 一张
    void add(const Cards& cards);   // 多张

    // 一次性插入多个数据 (操作符重载 << )  重载运算符<<插入一张或者多张牌
    Cards& operator <<(const Card& card);
    Cards& operator <<(const Cards& cards);

    // 删除扑克牌
    void remove(const Card& card);
    void remove(const Cards& cards);

    // 扑克牌的总数量
    int cardCount();
    // 判断是否为空
    bool isEmpty();
    // 清空
    void clear();

    // 最大点数
    Card::CardPoint maxPoint();
    // 最小点数
    Card::CardPoint minPoint();
    // 指定点数的牌的数量
    int pointCount(Card::CardPoint point);
    // 某张牌是否在集合中
    bool contains(const Card& card);
    bool contains(const Cards& cards);

    // 随机取出一张扑克牌
    Card takeRandCard();

    // QVector<Card>
    // QSet  -> QVector
    CardList toCardList(SortType type=Desc);   // 玩家手中的牌（默认降序）
private:
    QSet<Card> m_cards;
};

#endif // CARDS_H
