#include "transactionentity.h"
#include "entity.h"

TransactionEntity::TransactionEntity(long id, long from_card_id, long to_card_id, long amount, int type, long* automatic_transaction_id):
    Entity(id), _from_card_id(from_card_id), _to_card_id(to_card_id), _amount(amount), _type(type)
{
    if(automatic_transaction_id == nullptr) _automatic_transaction_id = nullptr;
    else _automatic_transaction_id = new long(*automatic_transaction_id);
}

TransactionEntity::TransactionEntity(const TransactionEntity& o) : Entity(o._id),
    _from_card_id(o._from_card_id), _to_card_id(o._to_card_id), _amount(o._amount), _type(o._type),
    _automatic_transaction_id(o._automatic_transaction_id)
{
    if(o._automatic_transaction_id != nullptr) _automatic_transaction_id = new long(*o._automatic_transaction_id);
}

TransactionEntity::~TransactionEntity()
{
    if(_automatic_transaction_id == nullptr) delete _automatic_transaction_id;
}

TransactionEntity& TransactionEntity::operator=(const TransactionEntity& o)
{
    Entity::operator=(o);
    _from_card_id = o._from_card_id;
    _to_card_id = o._to_card_id;
    _amount = o._amount;
    _type = o._type;
    if(o._automatic_transaction_id != nullptr) _automatic_transaction_id = new long(*o._automatic_transaction_id);
    return *this;
}
