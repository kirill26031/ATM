#include "automatictransactionservice.h"

AutomaticTransactionService* AutomaticTransactionService::_service = nullptr;

AutomaticTransactionService::AutomaticTransactionService() : _transaction_rep(TransactionRepositoryVectorImpl::getInstance()),
    _a_tr_rep(AutomaticTransactionRepositoryVectorImpl::getInstance()), _card_rep(CardRepositoryVectorImpl::getInstance()),
    _transaction_service(TransactionService::getInstance())
{

}

const AutomaticTransactionEntity& AutomaticTransactionService::getById(long id)
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

    AutomaticTransactionEntity a_tr(generateId(), from_card.id(), to_card.id(), amount, part, time_period,
                                    start_time-time_period);
    _a_tr_rep->setById(a_tr.id(), a_tr);
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
    for(const AutomaticTransactionEntity& a_tr : _a_tr_rep->getAll())
    {
        time_t now = time(0);
        long planned_money_to_spend = a_tr.amount();
        bool aborted_loop = false;
        for(time_t i = a_tr.startTime(); (now-i) >= a_tr.time_period(); i+=a_tr.time_period())
        {
            if(planned_money_to_spend >= a_tr.part())
            {
                bool sent = _transaction_service->Transfer(a_tr.part(), a_tr.fromCardId(), a_tr.toCardId(), new long(a_tr.id()));
                if(sent)
                {
                    planned_money_to_spend -= a_tr.part();
                }
                else {
                    aborted_loop = true;
                    break;
                }
            }
            else{
                bool sent = _transaction_service->Transfer(planned_money_to_spend, a_tr.fromCardId(), a_tr.toCardId(), new long(a_tr.id()));
                if(sent)
                {
                    planned_money_to_spend = 0;
                }
                else{
                    aborted_loop = true;
                }
                break;
            }
        }
        AutomaticTransactionEntity updated_a_tr(a_tr.id(), a_tr.fromCardId(), a_tr.toCardId(), planned_money_to_spend,
                                                a_tr.part(), a_tr.time_period(), a_tr.startTime());
        _a_tr_rep->setById(updated_a_tr.id(), updated_a_tr);
        if(aborted_loop) throw NotEnoughMoney("You can't send planned transaction");
    }
}
