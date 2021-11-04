#include "transactionrepositoryvectorimpl.h"

TransactionRepository* TransactionRepositoryVectorImpl::_rep = nullptr;

TransactionRepositoryVectorImpl::TransactionRepositoryVectorImpl() : TransactionRepository() {}


const TransactionEntity& TransactionRepositoryVectorImpl::getById(long id)
{
    for(TransactionEntity& e : _entities)
    {
        if(e.id() == id) return e;
    }
    throw NotFoundException(std::string("Transaction with id=").append(std::to_string(id)).append(" not found in TransactionRepository"));
}

const std::vector<TransactionEntity>& TransactionRepositoryVectorImpl::getAll()
{
    return _entities;
}

void TransactionRepositoryVectorImpl::setById(long id, TransactionEntity& Transaction)
{
    for(TransactionEntity& e : _entities)
    {
        if(e.id() == id)
        {
            e = Transaction;
            return;
        }
    }

    _entities.push_back(Transaction);
    //throw NotFoundException(std::string("Transaction with id=").append(std::to_string(id)).append(" not found in TransactionRepository"));
}

void TransactionRepositoryVectorImpl::deleteById(long id)
{
    if(id >= 0 && id < _entities.size())
    {
        _entities.erase(_entities.begin()+id);
    }
    else throw NotFoundException(std::string("Transaction with id=").append(std::to_string(id)).append(" not found in TransactionRepository"));
}

TransactionRepository* TransactionRepositoryVectorImpl::getInstance()
{
    if(_rep == nullptr) _rep = new TransactionRepositoryVectorImpl();
    return _rep;
}
