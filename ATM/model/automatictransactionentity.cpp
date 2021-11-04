#include "automatictransactionentity.h"
#include "entity.h"

AutomaticTransactionEntity::AutomaticTransactionEntity(long id, long from_card_id, long to_card_id, long amount, long part, long time_period, long elapsed_time):
    Entity(id), _from_card_id(from_card_id), _to_card_id(to_card_id), _amount(amount), _part(part), _time_period(time_period), _elapsed_time(elapsed_time) {}
