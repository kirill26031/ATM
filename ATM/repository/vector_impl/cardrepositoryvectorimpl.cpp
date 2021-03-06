#include "cardrepositoryvectorimpl.h"

CardRepository* CardRepositoryVectorImpl::_rep = nullptr;

CardRepositoryVectorImpl::CardRepositoryVectorImpl() : CardRepository()
{
//    _entities.push_back(CardEntity(0, 1234567890123456, 4455, 0, "Card 00", 300, 100, LONG_MAX, new long(1)));
//    _entities.push_back(CardEntity(1, 9012345612345678, 4545, 0, "Card 01", 400));
//    _entities.push_back(CardEntity(6, 9012345612345678, 4545, 0, "Card 02", 400, 300, LONG_MAX, new long(0)));
//    _entities.push_back(CardEntity(2, 1234123412341234, 4545, 1, "Card 10", 500, 0, 700, nullptr, new long(3)));
//    _entities.push_back(CardEntity(3, 1111111111111111, 4545, 1, "Card 11", 500));
//    _entities.push_back(CardEntity(4, 2222222222222222, 4545, 2, "Card 20", 500));
//    _entities.push_back(CardEntity(5, 3333333333333333, 4545, 2, "Card 21", 500));
}


CardEntity CardRepositoryVectorImpl::getById(long id)
{
    for(CardEntity& card : _entities)
    {
        if(card.id() == id) return card;
    }
    throw NotFoundException(std::string("Card with id=").append(std::to_string(id)).append(" not found in CardRepository"));
}

std::vector<CardEntity> CardRepositoryVectorImpl::getAll()
{
    return _entities;
}

void CardRepositoryVectorImpl::setById(long id, const CardEntity& card)
{
    for(CardEntity& c : _entities)
    {
        if(c.id() == id)
        {
            c = card;
            return;
        }
    }

    _entities.push_back(card);
    //throw NotFoundException(std::string("Card with id=").append(std::to_string(id)).append(" not found in CardRepository"));
}

void CardRepositoryVectorImpl::deleteById(long id)
{
    for(auto iter = _entities.begin(); iter != _entities.end(); ++iter)
    {
        if(iter->id() == id){
            _entities.erase(iter);
            break;
        }
    }
}

void CardRepositoryVectorImpl::clearAll()
{
    _entities.clear();
}

CardEntity CardRepositoryVectorImpl::getByCardId(long long card_id)
{
    for(CardEntity& card : _entities)
    {
        if(card.cardId() == card_id) return card;
    }
    throw NotFoundException(std::string("Card with requested cardId not found in CardRepository"));
}

CardRepository* CardRepositoryVectorImpl::getInstance()
{
    if(_rep == nullptr) _rep = new CardRepositoryVectorImpl();
    return _rep;
}

bool CardRepositoryVectorImpl::existsById(long id)
{
    for(CardEntity& e : _entities)
    {
        if(e.id() == id) return true;
    }
    return false;
}

std::vector<CardEntity> CardRepositoryVectorImpl::getCardsDependantOnThisByReserve(long id)
{
    std::vector<CardEntity> res;
    for(const CardEntity& card : getAll())
    {
        if(card.reserveCardId() != nullptr && *card.reserveCardId() == id) res.push_back(card);
    }
    return res;
}

std::vector<CardEntity> CardRepositoryVectorImpl::getCardsDependantOnThisByOverflow(long id)
{
    std::vector<CardEntity> res;
    for(const CardEntity& card : getAll())
    {
        if(card.overflowCardId() != nullptr && *card.overflowCardId() == id) res.push_back(card);
    }
    return res;
}
