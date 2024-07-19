#include "cards.h"
#include <QRandomGenerator>

Cards::Cards() {}

void Cards::add(const Card &card)
{
    m_cards.insert(card);
}

void Cards::add(const Cards &cards)
{
    m_cards.unite(cards.m_cards);      // 取并集
}

Cards &Cards::operator <<(const Card &card)
{
    add(card);
    return *this;
}

Cards& Cards::operator <<(const Cards& cards){
    add(cards);
    return *this;
}

void Cards::remove(const Card &card)
{
    m_cards.remove(card);
}

void Cards::remove(const Cards &cards)
{
    m_cards.subtract(cards.m_cards);        // 取交集
}

int Cards::cardCount()
{
    return m_cards.size();
}

bool Cards::isEmpty()
{
    return m_cards.isEmpty();
}

void Cards::clear()
{
    m_cards.clear();
}

Card::CardPoint Cards::maxPoint()
{
    Card::CardPoint maxx = Card::Card_Begin;
    if(!m_cards.isEmpty())
    {
        for(auto it = m_cards.begin(); it!=m_cards.end(); ++it)
        {
            if(it->point() > maxx)
            {
                maxx = it->point();
            }
        }
    }
    return maxx;
}

Card::CardPoint Cards::minPoint()
{
    Card::CardPoint minn = Card::Card_Begin;
    if(!m_cards.isEmpty())
    {
        for(auto it = m_cards.begin();it!=m_cards.end();++it)
        {
            if(it->point() < minn)
            {
                minn = it->point();
            }
        }
    }
    return minn;
}

int Cards::pointCount(Card::CardPoint point)     // 统计某张牌的个数
{
    int ans = 0;
    for(auto it = m_cards.begin();it!=m_cards.end();++it)
    {
        if(it->point() == point)
        {
            ans++;
        }
    }
    return ans;
}

bool Cards::contains(const Card &card)
{
    return m_cards.contains(card);
}

bool Cards::contains(const Cards &cards)
{
    return m_cards.contains(cards.m_cards);
}

Card Cards::takeRandCard()     // 随机抽取一张牌
{
    int num = QRandomGenerator::global()->bounded(m_cards.size());
    QSet<Card>::const_iterator it = m_cards.constBegin();
    for(int i =0;i<num;i++,it++){}
    Card card = *it;
    m_cards.erase(it);
    return card;
}

CardList Cards::toCardList(SortType type)       // 排序  默认降序
{
    CardList list;
    for(auto it=m_cards.begin();it!=m_cards.end();++it)
    {
        list<<*it;
    }

    if(type==Asc)
    {
        std::sort(list.begin(),list.end(),lessSort);
    }
    else if(type == Desc)
    {
        std::sort(list.begin(),list.end(),greaterSort);
    }
    return list;
}
