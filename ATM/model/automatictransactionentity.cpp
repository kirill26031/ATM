#include "automatictransactionentity.h"
#include "entity.h"

AutomaticTransactionEntity::AutomaticTransactionEntity(long id, long from_card_id, long to_card_id, long amount, long part, double time_period):
    Entity(id), from_card_id(from_card_id), to_card_id(to_card_id), amount(amount), part(part), time_period(time_period) {}
