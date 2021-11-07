#ifndef QAUTOTRANSACTIONITEM_H
#define QAUTOTRANSACTIONITEM_H

#include <QListWidgetItem>

#include <model/automatictransactionentity.h>
#include <repository/vector_impl/automatictransactionrepositoryvectorimpl.h>
#include <view/qcardnumberedit.h>
#include <view/qamountedit.h>
#include <model/cardentity.h>
#include <repository/vector_impl/cardrepositoryvectorimpl.h>

class QAutoTransactionItem : public QListWidgetItem
{


public:

    const long transaction_id;

    QAutoTransactionItem();  

    QAutoTransactionItem(long transaction_id, long card_id): QListWidgetItem(), transaction_id(transaction_id) {
        AutomaticTransactionEntity transaction = AutomaticTransactionRepositoryVectorImpl::getInstance()->getById(transaction_id);

        QString str = QAmountEdit::Amount(transaction.amount()) + " ";
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

#endif // QAUTOTRANSACTIONITEM_H
