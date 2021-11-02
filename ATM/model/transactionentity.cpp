#include "transactionentity.h"
#include "entity.h"

TransactionEntity::TransactionEntity(long id, long from_card_id, long to_card_id, long amount):
    Entity(id), _from_card_id(from_card_id), _to_card_id(to_card_id), _amount(amount) {}
