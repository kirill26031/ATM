#ifndef GLOBALSERVICE_H
#define GLOBALSERVICE_H

#include <model/transactionentity.h>
#include <model/cardentity.h>
#include <model/automatictransactionentity.h>
#include <model/userentity.h>

#include <repository/vector_impl/automatictransactionrepositoryvectorimpl.h>
#include <repository/vector_impl/cardrepositoryvectorimpl.h>
#include <repository/vector_impl/transactionrepositoryvectorimpl.h>
#include <repository/vector_impl/userrepositoryvectorimpl.h>

#include <repository/automatictransactionrepository.h>
#include <repository/cardrepository.h>
#include <repository/transactionrepository.h>
#include <repository/userrepository.h>

class GlobalService
{
public:
    GlobalService();

private:
    static bool GetMoney(long amount, long from_card_id, bool execute) {
        try {
            CardEntity from_card = CardRepositoryVectorImpl::getInstance()->getById(from_card_id);

            if (from_card.balance() - amount < from_card.minBalance()) {
                long lacks = from_card.minBalance() - (from_card.balance() - amount);
                bool result = GetMoney(lacks, *from_card.reserveCardId(), execute);
                if (!result) return false;
                if (execute) {
                    from_card.balance() = from_card.minBalance();
                    CardRepositoryVectorImpl::getInstance()->setById(from_card_id, from_card);
                }
                return true;
            } else {
                if (execute) {
                    from_card.balance() -= amount;
                    CardRepositoryVectorImpl::getInstance()->setById(from_card_id, from_card);
                }
                return true;
            }
        }  catch (NotFoundException ex) {
            return false;
        }
    }

    static bool AddMoney(long amount, long to_card_id, bool execute) {
        try {
            CardEntity to_card = CardRepositoryVectorImpl::getInstance()->getById(to_card_id);

            if (to_card.balance() + amount > to_card.maxBalance()) {
                long overflows = to_card.balance() + amount - to_card.maxBalance();
                bool result = AddMoney(overflows, *to_card.overflowCardId(), execute);
                if (!result) return false;
                if (execute) {
                    to_card.balance() = to_card.maxBalance();
                    CardRepositoryVectorImpl::getInstance()->setById(to_card_id, to_card);
                }
                return true;
            } else {
                if (execute) {
                    to_card.balance() += amount;
                    CardRepositoryVectorImpl::getInstance()->setById(to_card_id, to_card);
                }
                return true;
            }
        }  catch (NotFoundException ex) {
            return false;
        }
    }

public:
    //creates new transaction and transfer money between cards
    static bool Transfer(long amount, long from_card_id, long to_card_id) {
        CardEntity from_card = CardRepositoryVectorImpl::getInstance()->getById(from_card_id);
        CardEntity to_card = CardRepositoryVectorImpl::getInstance()->getById(to_card_id);
        bool can_execute = GetMoney(amount, from_card_id, false) && AddMoney(amount, to_card_id, false);
        if (can_execute) {
            GetMoney(amount, from_card_id, true);
            AddMoney(amount, to_card_id, true);

            TransactionEntity transaction = TransactionEntity(6666666/*id should be automatically generated*/, from_card_id, to_card_id, amount, 0, nullptr);
            TransactionRepositoryVectorImpl::getInstance()->setById(6666666, transaction);
            return true;
        } else {
            return false;
        }
    }


    static bool CheckCard(long card_id, int pin) {
        CardEntity card = CardRepositoryVectorImpl::getInstance()->getById(card_id);
        return card.pin() == pin;
    }


    static bool editPin(long long card_id, int pin) {
        try {
            CardEntity card = CardRepositoryVectorImpl::getInstance()->getById(card_id);
            card.pin() = pin;
            CardRepositoryVectorImpl::getInstance()->setById(card_id, card);
        } catch(const NotFoundException& nfe) {
            int x = 2 + 2;
        }
    }

    static bool AddAutomaticTransaction(long amount, long from_card_id, long to_card_id, long part) {
        //implement
    }

    static void UpdateAutomaticTransactions() {
        //implement
    }



    //private static GlobalService* _instance;

    //static GlobalService* getInstance() {
    //    return _instance
    //}
};

#endif // GLOBALSERVICE_H
