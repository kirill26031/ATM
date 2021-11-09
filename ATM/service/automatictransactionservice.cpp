#include "automatictransactionservice.h"

AutomaticTransactionService* AutomaticTransactionService::_service = nullptr;

AutomaticTransactionService::AutomaticTransactionService() : _transaction_rep(TransactionRepositoryVectorImpl::getInstance()),
    _a_tr_rep(AutomaticTransactionRepositoryVectorImpl::getInstance()), _card_rep(CardRepositoryVectorImpl::getInstance()),
    _transaction_service(TransactionService::getInstance())
{

}

AutomaticTransactionEntity AutomaticTransactionService::getById(long id)
{
    return _a_tr_rep->getById(id);
}

long AutomaticTransactionService::createAutomaticTransaction(long long from_card_n, long long to_card_n, long amount,
                                                             long part, long time_period, long start_time_offset)
{
    const CardEntity& from_card = _card_rep->getByCardId(from_card_n);
    const CardEntity& to_card = _card_rep->getByCardId(to_card_n);

    time_t now = time(0);
    time_t start_time = now + start_time_offset;

    AutomaticTransactionEntity a_tr(generateId(), from_card.id(), to_card.id(), amount, amount, part, time_period,
                                    start_time-time_period);
    _a_tr_rep->setById(-1, a_tr);
    return a_tr.id();
}

void AutomaticTransactionService::deleteAutomaticTransaction(long auto_tr_id)
{
    _a_tr_rep->deleteById(auto_tr_id);
}

std::vector<AutomaticTransactionEntity> AutomaticTransactionService::getAllAutomaticTransactionsFromMe(long sender_card_id)
{
    if(!_card_rep->existsById(sender_card_id))
    {
        throw NotFoundException("Card with id provided to AutomaticTransactionService::getAllAutomaticTransactionsFromMe was not found");
    }
    std::vector<AutomaticTransactionEntity> res;
    for(const AutomaticTransactionEntity& a_tr : _a_tr_rep->getAll())
    {
        if(a_tr.fromCardId() == sender_card_id) res.push_back(a_tr);
    }
    return res;
}

std::vector<AutomaticTransactionEntity> AutomaticTransactionService::getAllAutomaticTransactionsToMe(long receiver_card_id)
{
    if(!_card_rep->existsById(receiver_card_id))
    {
        throw NotFoundException("Card with id provided to AutomaticTransactionService::getAllAutomaticTransactionsToMe was not found");
    }
    std::vector<AutomaticTransactionEntity> res;
    for(const AutomaticTransactionEntity& a_tr : _a_tr_rep->getAll())
    {
        if(a_tr.toCardId() == receiver_card_id) res.push_back(a_tr);
    }
    return res;
}

void AutomaticTransactionService::checkAndExecute()
{
    auto auto_transactions(_a_tr_rep->getAll());
    std::set<ATE, std::function<bool (const ATE& a, const ATE& b)>> ates(
        [](const ATE& a, const ATE& b){
            if((a._last_executed_time+a._time_period) < (b._last_executed_time+b._time_period)) return true;
            if((a._last_executed_time+a._time_period) > (b._last_executed_time+b._time_period)) return false;
            return a._id < b._id;
        }
    );
    for(const AutomaticTransactionEntity& e : _a_tr_rep->getAll())
    {
        ATE ate;
        ate._id = e.id();
        ate._last_executed_time =  e.lastExecutedTime();
        ate._time_period = e.time_period();
        ate._total = e.total();
        ate._amount = e.amount();
        ate._part = e.part();
        ate._from_card_id = e.fromCardId();
        ate._to_card_id = e.toCardId();
        ate._aborted = e.aborted();
        ates.insert(ate);
    }

    time_t now = time(0);

    while(!ates.empty())
    {
        auto ate = *ates.begin();
        ates.erase(ates.begin());
        if(ate._last_executed_time + ate._time_period > now)
        {
            AutomaticTransactionEntity ch(ate._id, ate._from_card_id, ate._to_card_id, ate._total, ate._amount, ate._part, ate._time_period, ate._last_executed_time, ate._aborted);
            _a_tr_rep->setById(ch.id(), ch);
            continue;
        }
        long amount_to_remove = ate._part <= ate._amount ? ate._part : ate._amount;
        if(ate._amount == 0)
        {
            AutomaticTransactionEntity ch(ate._id, ate._from_card_id, ate._to_card_id, ate._total, 0, ate._part, ate._time_period, ate._last_executed_time, ate._aborted);
            _a_tr_rep->setById(ch.id(), ch);
        }
        else
        {
            bool sent = _transaction_service->Transfer(amount_to_remove, ate._from_card_id, ate._to_card_id, new long(ate._id));
            if(sent)
            {
                ate._amount-=amount_to_remove;
                ate._last_executed_time+=ate._time_period;
                ates.insert(ate);
            }
            else
            {
                ate._aborted = true;
                AutomaticTransactionEntity ch(ate._id, ate._from_card_id, ate._to_card_id, ate._total, ate._amount, ate._part, ate._time_period, ate._last_executed_time, ate._aborted);
                _a_tr_rep->setById(ch.id(), ch);
            }
        }
    }
}
