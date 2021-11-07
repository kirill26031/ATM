#include "widget.h"
#include "./ui_widget.h"
#include <repository/vector_impl/cardrepositoryvectorimpl.h>
#include <view/qcardnumberedit.h>
#include <QMessageBox>
#include <repository/vector_impl/transactionrepositoryvectorimpl.h>
#include <view/qtransactionitem.h>



/*
#include <view/qpinedit.h>
#include <view/qamountedit.h>
#include <view/qcardnumberedit.h>
*/


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_ok_button_clicked()
{
    long long number = ui->transaction_card_field->GetCardNumber();
    //long amount = u



    ui->screens_container->setCurrentIndex(3);


}


void Widget::on_cancel_button_clicked()
{
    ui->screens_container->setCurrentIndex(3);
}


void Widget::on_advanced_mode_check_box_stateChanged(int arg1)
{
    ui->advanced_widget->setVisible(arg1 == Qt::Checked);
}


void Widget::on_exit_button_clicked()
{
    ui->screens_container->setCurrentIndex(1);
}


void Widget::on_card_button_clicked()
{
    ui->screens_container->setCurrentIndex(0);
}


void Widget::on_transactions_button_clicked()
{
    ui->screens_container->setCurrentIndex(2);
}


void Widget::on_transfer_button_clicked()
{
    ui->screens_container->setCurrentIndex(4);
}


void Widget::on_transaction_exit_button_clicked()
{
    ui->screens_container->setCurrentIndex(3);
}


void Widget::on_init_submit_button_clicked()
{
    long long card_number = ui->init_card_field->GetCardNumber();
    int pin_code = ui->init_pin_code_field->text().toInt(nullptr);

    try {
        CardEntity card = CardRepositoryVectorImpl::getInstance()->getByCardId(card_number);
        if (card.pin() != pin_code) {
            QMessageBox::critical(nullptr, "Error", "Incorrect pin code");
            return;
        }

    }  catch (NotFoundException exception) {
        QMessageBox::critical(nullptr, "Error", "Incorrect card number");

        CardEntity card = CardEntity(012, 1111111111111111, 0000, 0, "test", 12342);
        CardRepositoryVectorImpl::getInstance()->setById(0, card);

        TransactionEntity tr = TransactionEntity(2, 012, 123, 2222, 1);
        TransactionRepositoryVectorImpl::getInstance()->setById(2, tr);
        return;
    }

    CardEntity card = CardRepositoryVectorImpl::getInstance()->getByCardId(card_number);
    InitATM(card);

    QMessageBox::information(nullptr, "Info", QString::number(card.cardId()));
    ui->screens_container->setCurrentIndex(3);
}


void Widget::on_cancel_changes_button_clicked()
{
    ui->screens_container->setCurrentIndex(3);
}


void Widget::on_save_changes_button_clicked()
{
    ui->screens_container->setCurrentIndex(3);
}


void Widget::on_auto_transactions_button_clicked()
{

}


void Widget::on_auto_cancel_button_clicked()
{

}


void Widget::on_auto_exit_button_clicked()
{

}

void Widget::InitATM(CardEntity card) {
    ui->balance_field_1->SetAmount(card.balance());
    ui->balance_field_2->SetAmount(card.balance());
    ui->pin_edit_field->SetPin(card.pin());
    ui->transaction_list->clear();
    for (TransactionEntity entity : TransactionRepositoryVectorImpl::getInstance()->getAll()) {
        if (entity.fromCardId() == card.id() || entity.toCardId() == card.id()) {
            ui->transaction_list->addItem(new QTransactionItem(entity.id(), card.id()));
        }
    }
}


void Widget::on_transaction_list_itemClicked(QListWidgetItem *item)
{
    long transaction_id = static_cast<QTransactionItem*>(item)->transaction_id;
    TransactionEntity transaction = TransactionRepositoryVectorImpl::getInstance()->getById(transaction_id);
    ui->transaction_card_field->SetCardNumber(transaction.fromCardId());

}


void Widget::on_auto_transaction_list_itemClicked(QListWidgetItem *item)
{

}

