#include "automaticTransactionrepositoryvectorimpl.h"
#include <ctime>

AutomaticTransactionRepository* AutomaticTransactionRepositoryVectorImpl::_rep = nullptr;

AutomaticTransactionRepositoryVectorImpl::AutomaticTransactionRepositoryVectorImpl() : AutomaticTransactionRepository() {
    _entities.push_back(AutomaticTransactionEntity(0, 0, 3, 10, 1, 20, time(0)-150));
}


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

    _entities.push_back(AutomaticTransaction);
    //throw NotFoundException(std::string("AutomaticTransaction with id=").append(std::to_string(id)).append(" not found in AutomaticTransactionRepository"));
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

bool AutomaticTransactionRepositoryVectorImpl::existsById(long id)
{
    for(AutomaticTransactionEntity& e : _entities)
    {
        if(e.id() == id) return true;
    }
    return false;
}
