#include "automatictransactionentity.h"
#include "entity.h"

AutomaticTransactionEntity::AutomaticTransactionEntity(long id, long from_card_id, long to_card_id, long total, long amount, long part,
                                                       long time_period, long long last_executed_time, bool aborted):
    Entity(id), _from_card_id(from_card_id), _to_card_id(to_card_id), _total(total), _amount(amount), _part(part),
    _time_period(time_period), _last_executed_time(last_executed_time), _aborted(aborted) {}
