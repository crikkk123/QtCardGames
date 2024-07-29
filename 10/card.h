#ifndef CARD_H
#define CARD_H

#include <QVector>

class Card
{
public:
    // 花色
    enum CardSuit
    {
        Suit_Begin,
        Diamond,    // 方块
        Club,       // 梅花
        Heart,      // 红桃
        Spade,      // 黑桃
        Suit_End,
    };

    // 点数
    enum CardPoint
    {
        Card_Begin,
        Card_3,
        Card_4,
        Card_5,
        Card_6,
        Card_7,
        Card_8,
        Card_9,
        Card_10,
        Card_J,
        Card_Q,
        Card_K,
        Card_A,
        Card_2,
        Card_SJ,   //    small  joker
        Card_BJ,    //   big   joker
        Card_End,
    };

    Card();
    Card(CardPoint point,CardSuit suit);     // 通过Card构造函数可以生成点数和花色不同的牌

    void setSuit(CardSuit suit);        // 设置花色
    void setPoint(CardPoint point);     // 设置点数
    CardSuit suit() const;      // 获取花色
    CardPoint point() const;    // 获取点数

private:
    CardSuit m_suit;       // 花色
    CardPoint m_point;      // 点数
};

// 对象比较  比较Card对象的时候的第三个参数
bool lessSort(const Card& c1,const Card& c2);
bool greaterSort(const Card& c1,const Card& c2);

// 操作符重载 ==   比较两张牌的花色和点数相同
bool operator == (const Card& left,const Card& right);

bool operator < (const Card& left,const Card& right);

// 重写全局函数  qHash    哈希值
uint qHash(const Card& card);

// 定义类型的别名
using CardList = QVector<Card>;

#endif // CARD_H
