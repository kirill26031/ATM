#ifndef QAUTOTRANSACTIONITEM_H
#define QAUTOTRANSACTIONITEM_H

#include <QListWidgetItem>

#include <model/automatictransactionentity.h>
//#include <repository/vector_impl/automatictransactionrepositoryvectorimpl.h>
#include <view/qcardnumberedit.h>
#include <view/qamountedit.h>
#include <model/cardentity.h>
//#include <repository/vector_impl/cardrepositoryvectorimpl.h>
#include "service/automatictransactionservice.h"
#include "service/cardservice.h"

class QAutoTransactionItem : public QListWidgetItem
{


public:

    const long transaction_id;

    QAutoTransactionItem() : _card_service(CardService::getInstance()),
        _auto_service(AutomaticTransactionService::getInstance()), transaction_id(1234) {}

    QAutoTransactionItem(long transaction_id, long card_id): QListWidgetItem(), _card_service(CardService::getInstance()),
        _auto_service(AutomaticTransactionService::getInstance()),
        transaction_id(transaction_id)
    {
        AutomaticTransactionEntity transaction = _auto_service->getById(transaction_id);

        QString str = QAmountEdit::Amount(transaction.amount()) + " ";
        if ((transaction.fromCardId()) == card_id) {
            CardEntity card = _card_service->getCardById(transaction.toCardId());
            str += "to " + QCardNumberEdit::CardNumber(card.cardId());
        } else {
            CardEntity card = _card_service->getCardById(transaction.fromCardId());
            str += "from " + QCardNumberEdit::CardNumber(card.cardId());
        }

        setText(str);
    }

private:
    CardService* _card_service;
    AutomaticTransactionService* _auto_service;
};

#endif // QAUTOTRANSACTIONITEM_H
