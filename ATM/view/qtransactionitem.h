#ifndef QTRANSACTIONITEM_H
#define QTRANSACTIONITEM_H

#include <QListWidgetItem>
//#include <repository/vector_impl/transactionrepositoryvectorimpl.h>
#include <model/transactionentity.h>
#include <view/qcardnumberedit.h>
#include <view/qamountedit.h>
#include <model/cardentity.h>
//#include <repository/vector_impl/cardrepositoryvectorimpl.h>
#include "service/cardservice.h"
#include "service/transactionservice.h"

class QTransactionItem : public QListWidgetItem
{
public:
    const long transaction_id;


    QTransactionItem(long transaction_id, long card_id): QListWidgetItem(), transaction_id(transaction_id) ,
        _card_service(CardService::getInstance()), _transaction_service(TransactionService::getInstance())
    {
        TransactionEntity transaction = _transaction_service->getById(transaction_id);


        QString str = QAmountEdit::Amount(transaction.amount())+" ";
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
    TransactionService* _transaction_service;
};

#endif // QTRANSACTIONITEM_H
