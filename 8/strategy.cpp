#include "strategy.h"
#include <functional>

Strategy::Strategy(Player *player, const Cards &cards)
{
    m_player = player;
    m_cards = cards;
}

Cards Strategy::makeStrategy()
{
    // 得到出牌玩家对象以及打出的牌
    Player* pendPlayer = m_player->getPendPlayer();
    Cards pendCards = m_player->getPendCards();

    // 判断上次出牌的玩家是不是我自己
    if(pendPlayer==m_player||pendPlayer==nullptr)
    {
        // 直接出牌
        // 如果不是我自己，出牌没有限制
        return firstPlay();
    }
    else
    {
        // 如果不是我自己需要找出比出牌玩家点数大的牌
        PlayHand type(pendCards);
        Cards beatCards = getGreaterCards(type);
        // 找到了点数大的牌需要考虑是否出牌
        bool shouldBeat =whetherToBeat(beatCards);
        if(shouldBeat)
        {
            return beatCards;
        }
        else
        {
            return Cards();
        }
    }
    return Cards();
}

Cards Strategy::firstPlay()
{

}

Cards Strategy::getGreaterCards(PlayHand type)
{
    // 1、出牌玩家和当前玩家不是一伙的
    Player* pendPlayer = m_player->getPendPlayer();
    if(pendPlayer->getRole()!=m_player->getRole() && pendPlayer->getCards().cardCount()<=3)
    {
        QVector<Cards> bombs = findCardsByCount(4);
        for(int i=0;i<bombs.size();i++)
        {
            if(PlayHand(bombs[i]).canBeat(type))
            {
                return bombs[i];
            }
        }
        // 搜索当前玩家是否有王炸
        Cards sj = findSamePointcards(Card::Card_SJ,1);
        Cards bj = findSamePointcards(Card::Card_BJ,1);
        if(!sj.isEmpty()&&!bj.isEmpty())
        {
            Cards jokers;
            jokers<<sj<<bj;
            return jokers;
        }
    }
    // 2、当前玩家和下一个玩家不是一伙的
    Player* nextPlayer = m_player->getNextPlayer();
    // 将玩家手中的顺子剔除出去
    Cards remain = m_cards;
    //remain.remove();

    auto beatCard = std::bind([=](Cards& cards){
        QVector<Cards> beatCardsArray = Strategy(m_player,cards).findCardType(type,true);
        if(!beatCardsArray.isEmpty())
        {
            if(m_player->getRole()!=nextPlayer->getRole()&&nextPlayer->getCards().cardCount()<=2)
            {
                return beatCardsArray.back();
            }
            else
            {
                return beatCardsArray.front();
            }
        }
        return Cards();
    },std::placeholders::_1);

    Cards cs;
    if(!beatCard(remain).isEmpty())
    {
        return cs;
    }
    else
    {
        if(!beatCard(m_cards).isEmpty())
        {
            return cs;
        }
    }
    return Cards();
}

bool Strategy::whetherToBeat(Cards &cs)
{
    // 没有找到能够击败对方的牌
    if(cs.isEmpty())
    {
        return false;
    }

    // 得到出牌玩家的对象
    Player* pendPlayer = m_player->getPendPlayer();
    if(pendPlayer->getRole() == m_player->getRole())
    {
        // 手里的牌所剩无几并且是一个完整的牌型
        Cards left = m_cards;
        left.remove(cs);
        if(PlayHand(left).getHandType()!=PlayHand::Hand_Unknown)
        {
            return true;
        }
        // 如果cs对象中的牌最小点数是2，大小王，---》不出牌
        Card::CardPoint basePoint = PlayHand(cs).getCardPoint();
        if(basePoint==Card::Card_2||basePoint==Card::Card_SJ||basePoint==Card::Card_BJ)
        {
            return false;
        }
    }
    else
    {
        PlayHand myHand(cs);
        // 如果是三个2带1，或者带一对，不出牌（保存实力）
        if((myHand.getHandType()==PlayHand::Hand_Triple_Single||myHand.getHandType()==PlayHand::Hand_Triple_Pair)
                && myHand.getCardPoint()==Card::Card_2)
        {
            return false;
        }

        // 如果cs是对2，并且出牌玩家手中的牌的数量大于等于10,&&自己的牌的数量大于等于5，暂时放弃出牌
        if(myHand.getHandType()==PlayHand::Hand_Pair&&myHand.getCardPoint()==Card::Card_2
            &&pendPlayer->getCards().cardCount()>=10&&m_player->getCards().cardCount()>=5)
        {
            return false;
        }
    }
    return true;
}

// 找到count张点数为point的牌
Cards Strategy::findSamePointcards(Card::CardPoint point, int count)
{
    if(count<1||count>4)
    {
        return Cards();
    }
    // 大小王
    if(point==Card::Card_SJ||point==Card::Card_BJ)
    {
        if(count>1)
        {
            return Cards();
        }
        // 手里的牌是否包含那张牌，不包含返回空的
        Card card;
        card.setPoint(point);
        card.setSuit(Card::Suit_Begin);
        if(m_cards.contains(card))
        {
            Cards cards;
            cards.add(card);
            return cards;
        }
        return Card();
    }

    // 不是大小王
    int findCount = 0;
    Cards findCards;
    for(int suit=Card::Suit_Begin+1;suit<Card::Suit_End;suit++)
    {
        Card card;
        card.setPoint(point);
        card.setSuit((Card::CardSuit)suit);
        // 找某张牌，先创建这张牌，看手里的牌是否包含这张牌
        if(m_cards.contains(card))
        {
            findCount++;
            findCards.add(card);
            if(findCount==count)
            {
                return findCards;
            }
        }
    }
    return Cards();
}

// 找出所有count个数的牌  比如count为2，找出所有的对
QVector<Cards> Strategy::findCardsByCount(int count)
{
    if(count<1||count>4)
    {
        return QVector<Cards>();
    }

    QVector<Cards> cardsArray;
    for(Card::CardPoint point=Card::Card_3;point<Card::Card_End;point=(Card::CardPoint)(point+1))
    {
        if(m_cards.pointCount(point)==count)        // pointCount 点数为point牌的数量
        {
            Cards cs;
            cs << findSamePointcards(point,count);      // ???
            cardsArray.push_back(cs);
        }
    }
    return cardsArray;
}

Cards Strategy::getRangeCards(Card::CardPoint begin, Card::CardPoint end)
{
    Cards rangeCards;
    for(Card::CardPoint point=begin;point<end;point=(Card::CardPoint)(point+1))
    {
        int count = m_cards.pointCount(point);  // pointCount 点数为point牌的数量
        Cards cs = findSamePointcards(point,count);     // ???
        rangeCards<< cs;
    }
    return rangeCards;
}

// 类型相同的情况下beat的作用是新找到的牌比旧牌的点数要大
QVector<Cards> Strategy::findCardType(PlayHand hand, bool beat)
{
    PlayHand::HandType type = hand.getHandType();
    Card::CardPoint point = hand.getCardPoint();
    int extra = hand.getExtra();

    Card::CardPoint beginPoint = beat?Card::CardPoint(point+1):Card::Card_3;

    switch(type)
    {
    case PlayHand::Hand_Single:
        return getCards(beginPoint,1);
    case PlayHand::Hand_Pair:
        return getCards(beginPoint,2);
    case PlayHand::Hand_Triple:
        return getCards(beginPoint,3);
    case PlayHand::Hand_Triple_Single:
        return getTripleSingleorPair(beginPoint,PlayHand::Hand_Single);
    case PlayHand::Hand_Triple_Pair:
        return getTripleSingleorPair(beginPoint,PlayHand::Hand_Pair);
    case PlayHand::Hand_Plane:
        return getPlane(beginPoint);
    case PlayHand::Hand_Plane_Two_Single:
        return getPlane2SingleOr2Pair(beginPoint,PlayHand::Hand_Single);
    case PlayHand::Hand_Plane_Two_Pair:
        return getPlane2SingleOr2Pair(beginPoint,PlayHand::Hand_Pair);
    case PlayHand::Hand_Seq_Pair:
    {
        CardInfo info;
        info.begin = beginPoint;
        info.end = Card::Card_Q;
        info.number = 2;
        info.base = 3;
        info.extra = extra;
        info.beat = beat;
        info.getSeq = &Strategy::getbaseSeqPair;
        return getSepPairOrSeqSingle(info);
    }
    case PlayHand::Hand_Seq_Single:
    {
        CardInfo info;
        info.begin = beginPoint;
        info.end = Card::Card_10;
        info.number = 1;
        info.base = 5;
        info.extra = extra;
        info.beat = beat;
        info.getSeq = &Strategy::getbaseSeqSingle;
        return getSepPairOrSeqSingle(info);
    }
    case PlayHand::Hand_Bomb:
        return getBomb(beginPoint);
    default:
        return QVector<Cards>();
    }
}

// 从点数point找到最后  牌的个数是number
QVector<Cards> Strategy::getCards(Card::CardPoint point, int number)
{
    QVector<Cards> findCardsArray;
    for(Card::CardPoint pt = point;pt<Card::Card_End; pt =(Card::CardPoint)(pt+1))
    {
        // 目的是尽量不拆分别的牌型
        if(m_cards.pointCount(pt)== number)
        {
            Cards cs = findSamePointcards(pt,number);
            findCardsArray<<cs;
        }
    }

    return findCardsArray;
}

QVector<Cards> Strategy::getTripleSingleorPair(Card::CardPoint begin, PlayHand::HandType type)
{
    // 三带一或对 先找到点数相同的三张牌
    QVector<Cards> findCardArray = getCards(begin,3);
    if(!findCardArray.isEmpty())
    {
        // 将找到的牌从用户手中删除
        Cards remainCards = m_cards;
        remainCards.remove(findCardArray);
        // 搜索牌型
        // 搜索单牌或者成对的牌
        Strategy st(m_player,remainCards);
        // 递归调用
        QVector<Cards> cardsArray = st.findCardType(PlayHand(type,Card::Card_Begin,0),false);
        if(!cardsArray.isEmpty())
        {
            // 将找到的牌和三张点数相同的牌进行组合  相互组合
            for(int i =0;i<findCardArray.size();i++)
            {
                findCardArray[i].add(cardsArray.at(i));
            }
        }
        else
        {
            findCardArray.clear();
        }
    }

    // 将最终结果返回给函数调用者
    return findCardArray;
}

QVector<Cards> Strategy::getPlane(Card::CardPoint begin)
{
    QVector<Cards> findCardArray;
    for(Card::CardPoint pt = begin;pt<=Card::Card_K; pt =(Card::CardPoint)(pt+1))
    {
        // 根据点数和数量进行搜索
        Cards prevCards = findSamePointcards(pt,3);
        Cards nextCards = findSamePointcards((Card::CardPoint)(pt+1),3);
        if(!prevCards.isEmpty()&&!nextCards.isEmpty())
        {
            Cards tmp;
            tmp<<prevCards<<nextCards;
            findCardArray<<tmp;
        }
    }
    return findCardArray;
}

QVector<Cards> Strategy::getPlane2SingleOr2Pair(Card::CardPoint begin, PlayHand::HandType type)
{
    // 找飞机
    QVector<Cards> findCardArray = getPlane(begin);
    if(!findCardArray.isEmpty())
    {
        // 将找到的牌从用户手中删除
        Cards remainCards = m_cards;
        remainCards.remove(findCardArray);
        // 搜索牌型
        // 搜索单牌或者成对的牌
        Strategy st(m_player,remainCards);
        // 递归找单和对
        QVector<Cards> cardsArray = st.findCardType(PlayHand(type,Card::Card_Begin,0),false);
        if(cardsArray.size()>=2)
        {
            // 找到了，将其添加到飞机组合中
            for(int i =0;i<findCardArray.size();i++)
            {
                Cards tmp;
                tmp<<cardsArray[0]<<cardsArray[1];
                findCardArray[i].add(tmp);
            }
        }
        else
        {
            findCardArray.clear();
        }
    }
    return findCardArray;
}

QVector<Cards> Strategy::getSepPairOrSeqSingle(CardInfo& info)
{
    QVector<Cards> findCardsArray;
    if(info.beat)
    {
        // 最少3个，最大A
        for(Card::CardPoint pt = info.begin;pt<=info.end; pt =(Card::CardPoint)(pt+1))
        {
            bool found = true;
            Cards seqCards;
            for(int i=0;i<info.extra;++i)
            {
                // 基于点数和数量进行牌的搜索
                Cards cards = findSamePointcards((Card::CardPoint)(pt+i),info.number);
                if(cards.isEmpty()||(pt+info.extra>=Card::Card_2))
                {
                    found = false;
                    seqCards.clear();
                    break;
                }
                else
                {
                    seqCards<< cards;
                }
            }
            if(found)
            {
                findCardsArray<<seqCards;
                return findCardsArray;
            }
        }
    }
    else
    {
        for(Card::CardPoint pt = info.begin;pt<=info.end; pt =(Card::CardPoint)(pt+1))
        {
            // 将找到的这个基础对存储起来
            Cards baseSep = (this->*info.getSeq)(pt);
            if(baseSep.isEmpty())
            {
                continue;
            }

            // 连对存储到容器中
            findCardsArray<<baseSep;

            int followed = info.base;
            Cards alreadyFollowedCards; // 存储后续找到的满足条件的连对

            // 不断的去找，比如连对 存储的是这样的  334455   33445566   3344556677 ...
            while(true)
            {
                // 新的起始点数
                Card::CardPoint followedPoint = (Card::CardPoint)(pt+followed);
                // 判断是否超出了上限
                if(followedPoint>=Card::Card_2)
                {
                    break;
                }
                Cards followedCards = findSamePointcards(followedPoint,info.number); // 连对个数为2
                if(followedCards.isEmpty())
                {
                    break;
                }
                else
                {
                    alreadyFollowedCards<<followedCards;
                    Cards newSep = baseSep;
                    newSep<<alreadyFollowedCards;
                    findCardsArray<<newSep;
                    followed++;
                }
            }
        }
    }
    return findCardsArray;
}

Cards Strategy::getbaseSeqPair(Card::CardPoint point)
{
    Cards cards0 = findSamePointcards(point,2);
    Cards cards1 = findSamePointcards((Card::CardPoint)(point+1),2);
    Cards cards2 = findSamePointcards((Card::CardPoint)(point+2),2);
    Cards baseSeq;
    if(!cards0.isEmpty()&&!cards1.isEmpty()&&!cards2.isEmpty())
    {
        baseSeq<<cards0<<cards1<<cards2;
    }
    return baseSeq;
}

Cards Strategy::getbaseSeqSingle(Card::CardPoint point)
{
    Cards cards0 = findSamePointcards(point,1);
    Cards cards1 = findSamePointcards((Card::CardPoint)(point+1),1);
    Cards cards2 = findSamePointcards((Card::CardPoint)(point+2),1);
    Cards cards3 = findSamePointcards((Card::CardPoint)(point+3),1);
    Cards cards4 = findSamePointcards((Card::CardPoint)(point+4),1);
    Cards baseSeq;
    if(!cards0.isEmpty()&&!cards1.isEmpty()&&!cards2.isEmpty()
        &&!cards3.isEmpty()&&!cards4.isEmpty())
    {
        baseSeq<<cards0<<cards1<<cards2<<cards3<<cards4;
    }
    return baseSeq;
}

QVector<Cards> Strategy::getBomb(Card::CardPoint begin)
{
    QVector<Cards> findCardsArray;
    for(Card::CardPoint point = begin;point<Card::Card_End;(Card::CardPoint)(point+1))
    {
        Cards cs = findSamePointcards(point,4);
        if(!cs.isEmpty())
        {
            findCardsArray<<cs;
        }
    }
    return findCardsArray;
}
