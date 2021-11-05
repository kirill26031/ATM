#include "transactionservice.h"

TransactionService* TransactionService::_service = nullptr;

TransactionService::TransactionService() : _card_rep(CardRepositoryVectorImpl::getInstance()),
    _transaction_rep(TransactionRepositoryVectorImpl::getInstance())
{

}

bool TransactionService::Transfer(long amount, long from_card_id, long to_card_id, long* automatic_transaction_id)
{
    bool can_execute = GetMoney(amount, from_card_id, to_card_id, false, false) && AddMoney(amount, from_card_id, to_card_id, false, false);
    if (can_execute)
    {
        GetMoney(amount, from_card_id, to_card_id, true, false);
        AddMoney(amount, from_card_id, to_card_id, true, false);
        TransactionEntity transaction(generateId(), from_card_id, to_card_id, amount,
                                      (automatic_transaction_id == nullptr ? 0 : 1), automatic_transaction_id);
        _transaction_rep->setById(transaction.id(), transaction);
        return true;
    } else {
        return false;
    }
}

/** Method can be used to check ability to transfer money (or do it) from 2 cards using reserved card system
 * execute - should method change data in repository (is this real transaction or check)
 * dependant - is checked transaction is part of reserve system chain execution
*/
bool TransactionService::GetMoney(long amount, long from_card_id, long to_card_id, bool execute, bool dependant) {
    try {
        const CardEntity& from_card = _card_rep->getById(from_card_id);

        if (from_card.balance() - amount < from_card.minBalance()) {
            long lacks = from_card.minBalance() - (from_card.balance() - amount);
            if(from_card.reserveCardId() == nullptr) return false;
            bool result = GetMoney(lacks, *from_card.reserveCardId(), from_card_id, execute, true);
            if (!result) return false;
            if (execute) {
                //from_card.balance() = from_card.minBalance();
                CardEntity updated_from_card(from_card.id(), from_card.cardId(), from_card.pin(), from_card.userId(),
                                             from_card.name(), from_card.minBalance(), from_card.minBalance(),
                                             from_card.maxBalance(), from_card.reserveCardId(), from_card.overflowCardId());
                _card_rep->setById(from_card_id, updated_from_card);
                //TODO: add transaction
                if(dependant){
                    TransactionEntity dep_tr(generateId(), from_card_id, to_card_id,
                                             amount, 2, nullptr);
                    _transaction_rep->setById(dep_tr.id(), dep_tr);
                }
            }
            return true;
        } else {
            if (execute) {
                //from_card.balance() -= amount;
                CardEntity updated_from_card(from_card.id(), from_card.cardId(), from_card.pin(), from_card.userId(),
                                             from_card.name(), from_card.balance()-amount, from_card.minBalance(),
                                             from_card.maxBalance(), from_card.reserveCardId(), from_card.overflowCardId());
                _card_rep->setById(from_card_id, updated_from_card);

                if(dependant){
                    TransactionEntity dep_tr(generateId(), from_card_id, to_card_id, amount, 2, nullptr);
                    _transaction_rep->setById(dep_tr.id(), dep_tr);
                }
            }
            return true;
        }
    }  catch (const NotFoundException& ex) {
        return false;
    }
}

/** Method can be used to check ability to transfer money (or do it) from 2 cards using overflow card system
 * execute - should method change data in repository (is this real transaction or check)
 * dependant - is checked transaction is part of overflow system chain execution
*/
bool TransactionService::AddMoney(long amount, long from_card_id, long to_card_id, bool execute, bool dependant) {
    try {
        const CardEntity& to_card = _card_rep->getById(to_card_id);

        if (to_card.balance() + amount > to_card.maxBalance()) {
            long overflows = to_card.balance() + amount - to_card.maxBalance();
            if(to_card.overflowCardId() == nullptr) return false;
            bool result = AddMoney(overflows, to_card_id, *to_card.overflowCardId(), execute, true);
            if (!result) return false;
            if (execute) {
                //to_card.balance() = to_card.maxBalance();
                CardEntity updated_to_card(to_card.id(), to_card.cardId(), to_card.pin(), to_card.userId(),
                                             to_card.name(), to_card.maxBalance(), to_card.minBalance(),
                                             to_card.maxBalance(), to_card.reserveCardId(), to_card.overflowCardId());
                _card_rep->setById(to_card_id, updated_to_card);
                //TODO: transaction
                if(dependant){
                    TransactionEntity dep_tr(generateId(), from_card_id, to_card_id,
                                             amount, 3, nullptr);
                    _transaction_rep->setById(dep_tr.id(), dep_tr);
                }
            }
            return true;
        } else {
            if (execute) {
//                to_card.balance() += amount;
                CardEntity updated_to_card(to_card.id(), to_card.cardId(), to_card.pin(), to_card.userId(),
                                             to_card.name(), to_card.balance()+amount, to_card.minBalance(),
                                             to_card.maxBalance(), to_card.reserveCardId(), to_card.overflowCardId());
                _card_rep->setById(to_card_id, updated_to_card);
                if(dependant){
                    TransactionEntity dep_tr(generateId(), from_card_id, to_card_id, amount, 3, nullptr);
                    _transaction_rep->setById(dep_tr.id(), dep_tr);
                }
            }
            return true;
        }
    }  catch (const NotFoundException& ex) {
        return false;
    }
}


std::vector<TransactionEntity> TransactionService::getSentTransactions(long sender_card_id)
{
//    const CardEntity& sender = _card_rep->getById(sender_card_id);
    if(!_card_rep->existsById(sender_card_id))
    {
        throw NotFoundException("Card with id proided to TransactionService::getSentTransactions was not found");
    }
    std::vector<TransactionEntity> res;
    for(const TransactionEntity& tr : _transaction_rep->getAll())
    {
        if(tr.fromCardId() == sender_card_id) res.push_back(tr);
    }
    return res;
}

std::vector<TransactionEntity> TransactionService::getReceivedTransactions(long receiver_card_id)
{
    if(!_card_rep->existsById(receiver_card_id))
    {
        throw NotFoundException("Card with id proided to TransactionService::getReceivedTransactions was not found");
    }
    std::vector<TransactionEntity> res;
    for(const TransactionEntity& tr : _transaction_rep->getAll())
    {
        if(tr.toCardId() == receiver_card_id) res.push_back(tr);
    }
    return res;
}

bool TransactionService::makeTransfer(long amount, long long from_card_n, long long to_card_n)
{
    const CardEntity& from = _card_rep->getByCardId(from_card_n);
    const CardEntity& to = _card_rep->getByCardId(to_card_n);
    return Transfer(amount, from.id(), to.id());
}

const TransactionEntity& TransactionService::getById(long id)
{
    return _transaction_rep->getById(id);
}
