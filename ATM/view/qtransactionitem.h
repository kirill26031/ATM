#ifndef QTRANSACTIONITEM_H
#define QTRANSACTIONITEM_H

#include <QListWidgetItem>
#include <repository/vector_impl/transactionrepositoryvectorimpl.h>
#include <model/transactionentity.h>
#include <view/qcardnumberedit.h>
#include <view/qamountedit.h>
#include <model/cardentity.h>
#include <repository/vector_impl/cardrepositoryvectorimpl.h>

class QTransactionItem : public QListWidgetItem
{
public:
    const long transaction_id;


    QTransactionItem(long transaction_id, long card_id): QListWidgetItem(), transaction_id(transaction_id) {
        TransactionEntity transaction = TransactionRepositoryVectorImpl::getInstance()->getById(transaction_id);


        QString str = QAmountEdit::Amount(transaction.amount())+" ";
        if ((transaction.fromCardId()) == card_id) {
            CardEntity card = CardRepositoryVectorImpl::getInstance()->getById(transaction.toCardId());
            str += "to " + QCardNumberEdit::CardNumber(card.cardId());
        } else {
            CardEntity card = CardRepositoryVectorImpl::getInstance()->getById(transaction.fromCardId());
            str += "from " + QCardNumberEdit::CardNumber(card.cardId());
        }

        setText(str);
    }
};

#endif // QTRANSACTIONITEM_H
