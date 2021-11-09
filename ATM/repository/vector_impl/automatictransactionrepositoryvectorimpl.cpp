#include "automatictransactionrepositoryvectorimpl.h"
#include <ctime>

AutomaticTransactionRepository* AutomaticTransactionRepositoryVectorImpl::_rep = nullptr;

AutomaticTransactionRepositoryVectorImpl::AutomaticTransactionRepositoryVectorImpl() : AutomaticTransactionRepository() {
//    _entities.push_back(AutomaticTransactionEntity(0, 0, 3, 10, 10, 1, 20, time(0)-150));
}


AutomaticTransactionEntity AutomaticTransactionRepositoryVectorImpl::getById(long id)
{
    for(AutomaticTransactionEntity& e : _entities)
    {
        if(e.id() == id) return e;
    }
    throw NotFoundException(std::string("AutomaticTransaction with id=").append(std::to_string(id)).append(" not found in AutomaticTransactionRepository"));
}

std::vector<AutomaticTransactionEntity> AutomaticTransactionRepositoryVectorImpl::getAll()
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
    for(auto iter = _entities.begin(); iter != _entities.end(); ++iter)
    {
        if(iter->id() == id){
            _entities.erase(iter);
            break;
        }
    }
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
