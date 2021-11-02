#include "automaticTransactionrepositoryvectorimpl.h"

AutomaticTransactionRepository* AutomaticTransactionRepositoryVectorImpl::_rep = nullptr;

AutomaticTransactionRepositoryVectorImpl::AutomaticTransactionRepositoryVectorImpl() : AutomaticTransactionRepository() {}


const AutomaticTransactionEntity& AutomaticTransactionRepositoryVectorImpl::getById(long id)
{
    for(AutomaticTransactionEntity& e : _entities)
    {
        if(e.id() == id) return e;
    }
    throw NotFoundException(std::string("AutomaticTransaction with id=").append(std::to_string(id)).append(" not found in AutomaticTransactionRepository"));
}

const std::vector<AutomaticTransactionEntity>& AutomaticTransactionRepositoryVectorImpl::getAll()
{
    return _entities;
}

void AutomaticTransactionRepositoryVectorImpl::setById(long id, AutomaticTransactionEntity& AutomaticTransaction)
{
    for(AutomaticTransactionEntity& e : _entities)
    {
        if(e.id() == id)
        {
            e = AutomaticTransaction;
            return;
        }
    }
    throw NotFoundException(std::string("AutomaticTransaction with id=").append(std::to_string(id)).append(" not found in AutomaticTransactionRepository"));
}

void AutomaticTransactionRepositoryVectorImpl::deleteById(long id)
{
    if(id >= 0 && id < _entities.size())
    {
        _entities.erase(_entities.begin()+id);
    }
    else throw NotFoundException(std::string("AutomaticTransaction with id=").append(std::to_string(id)).append(" not found in AutomaticTransactionRepository"));
}

AutomaticTransactionRepository* AutomaticTransactionRepositoryVectorImpl::getInstance()
{
    if(_rep == nullptr) _rep = new AutomaticTransactionRepositoryVectorImpl();
    return _rep;
}
