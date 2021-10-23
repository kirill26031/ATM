#include "cardrepositoryimpl.h"

CardRepositoryImpl::CardRepositoryImpl() : _entities(std::vector<CardEntity>())
{
}

CardRepositoryImpl::~CardRepositoryImpl(){}

const CardEntity& CardRepositoryImpl::getById(long id)
{
    for(CardEntity& card : _entities)
    {
        if(card._id == id) return card;
    }
    throw NotFoundException(std::string("Card with id=").append(std::to_string(id)).append(" not found in CardRepository"));
}

const std::vector<CardEntity>& CardRepositoryImpl::getAll()
{
    return _entities;
}

void CardRepositoryImpl::setById(long id, CardEntity& card)
{
    for(CardEntity& c : _entities)
    {
        if(c._id == id)
        {
            c = card;
            break;
        }
    }
    throw NotFoundException(std::string("Card with id=").append(std::to_string(id)).append(" not found in CardRepository"));
}

void CardRepositoryImpl::deleteById(long id)
{
    if(id >= 0 && id < _entities.size())
    {
        _entities.erase(_entities.begin()+id);
    }
    else throw NotFoundException(std::string("Card with id=").append(std::to_string(id)).append(" not found in CardRepository"));
}

const CardEntity& CardRepositoryImpl::getByCardId(std::array<int, 16> cardId)
{
    for(CardEntity& card : _entities)
    {
        if(card._cardId == cardId) return card;
    }
    throw NotFoundException(std::string("Card with requested cardId not found in CardRepository"));
}
