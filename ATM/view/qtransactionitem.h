#ifndef QTRANSACTIONITEM_H
#define QTRANSACTIONITEM_H

#include <QListWidgetItem>
#include <repository/vector_impl/transactionrepositoryvectorimpl.h>
#include <model/transactionentity.h>
#include <view/qcardnumberedit.h>

class QTransactionItem : public QListWidgetItem
{
public:
    const long transaction_id;


    QTransactionItem(long transaction_id, long card_id): QListWidgetItem(), transaction_id(transaction_id) {
        TransactionEntity transaction = TransactionRepositoryVectorImpl::getInstance()->getById(transaction_id);

        QString str = QString::number(transaction.amount())+"$ ";
        if ((transaction.fromCardId()) == card_id) {
            str += "to " + QCardNumberEdit::CardNumber(transaction.toCardId());
        } else {
            str += "from " + QCardNumberEdit::CardNumber(transaction.fromCardId());
        }

        setText(str);
    }
};

#endif // QTRANSACTIONITEM_H
