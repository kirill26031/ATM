#include "cardrepositoryimpl.h"

CardRepository* CardRepositoryImpl::_rep = nullptr;

CardRepositoryImpl::CardRepositoryImpl()
{
    _entities.push_back(CardEntity(0, {1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6}, {4, 4, 5, 5}, 0, "Card 1", 300));
    _entities.push_back(CardEntity(1, {9, 0, 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 7, 8}, {4, 5, 4, 5}, 0, "Card 2", 400));
}


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
            return;
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

CardRepository* CardRepositoryImpl::getInstance()
{
    if(_rep == nullptr) _rep = new CardRepositoryImpl();
    return _rep;
}
