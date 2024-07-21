#include "card.h"

Card::Card()
{

}

Card::Card(CardPoint point, CardSuit suit)
{
    setPoint(point);
    setSuit(suit);
}

void Card::setSuit(CardSuit suit){
    m_suit = suit;
}

void Card::setPoint(CardPoint point){
    m_point = point;
}

Card::CardSuit Card::suit() const{
    return m_suit;
}

Card::CardPoint Card::point() const{
    return m_point;
}

bool lessSort(const Card &c1, const Card &c2)
{
    if(c1.point() == c2.point())
    {
        return c1.suit()<c2.suit();
    }
    else
    {
        return c1.point()<c2.point();
    }
}

bool greaterSort(const Card& c1,const Card& c2)
{
    if(c1.point() == c2.point())
    {
        return c1.suit()>c2.suit();
    }
    else
    {
        return c1.point()>c2.point();
    }
}

bool operator == (const Card& left,const Card& right)
{
    return (left.point()==right.point() && left.suit()==right.suit());
}

uint qHash(const Card &card)
{
    return card.point()*100+card.suit();
}

bool operator < (const Card& left,const Card& right)
{
    if(left.point()< right.point())
    {
        return true;
    }
    else
    {
        return false;
    }
}
