#include "cardrepositoryvectorimpl.h"

CardRepository* CardRepositoryVectorImpl::_rep = nullptr;

CardRepositoryVectorImpl::CardRepositoryVectorImpl() : CardRepository()
{
    _entities.push_back(CardEntity(0, 1234567890123456, 4455, 0, "Card 1", 300));
    _entities.push_back(CardEntity(1, 9012345612345678, 4545, 0, "Card 2", 400));
}


const CardEntity& CardRepositoryVectorImpl::getById(long id)
{
    for(CardEntity& card : _entities)
    {
        if(card.id() == id) return card;
    }
    throw NotFoundException(std::string("Card with id=").append(std::to_string(id)).append(" not found in CardRepository"));
}

const std::vector<CardEntity>& CardRepositoryVectorImpl::getAll()
{
    return _entities;
}

void CardRepositoryVectorImpl::setById(long id, CardEntity& card)
{
    for(CardEntity& c : _entities)
    {
        if(c.id() == id)
        {
            c = card;
            return;
        }
    }
    throw NotFoundException(std::string("Card with id=").append(std::to_string(id)).append(" not found in CardRepository"));
}

void CardRepositoryVectorImpl::deleteById(long id)
{
    if(id >= 0 && id < _entities.size())
    {
        _entities.erase(_entities.begin()+id);
    }
    else throw NotFoundException(std::string("Card with id=").append(std::to_string(id)).append(" not found in CardRepository"));
}

const CardEntity& CardRepositoryVectorImpl::getByCardId(long long card_id)
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
