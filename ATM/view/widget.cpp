#include "widget.h"
#include "./ui_widget.h"
#include <repository/vector_impl/cardrepositoryvectorimpl.h>
#include <view/qcardnumberedit.h>
#include <QMessageBox>
#include <repository/vector_impl/transactionrepositoryvectorimpl.h>
#include <view/qtransactionitem.h>
#include <view/qautotransactionitem.h>
#include <repository/vector_impl/automatictransactionrepositoryvectorimpl.h>
#include <service/automatictransactionservice.h>
#include <service/transactionservice.h>
#include <model/automatictransactionentity.h>
#include <service/cardservice.h>

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
    long long number = ui->transfer_card_field->GetCardNumber();
    long sum = ui->sum_field->GetAmount();

    try {
        CardEntity curr_card = CardRepositoryVectorImpl::getInstance()->getById(current_card_id);
        CardEntity card = CardRepositoryVectorImpl::getInstance()->getByCardId(number);


        if (sum == -1) {
            QMessageBox::critical(nullptr, "Error", "Sum does not specified!");
            return;
        }



        if (ui->advanced_mode_check_box->checkState() == Qt::Checked) {
            long time_period = ui->time_period_field->GetAmount();
            long sum_per_time = ui->sum_per_time_field->GetAmount();

            if (time_period == -1) {
                QMessageBox::critical(nullptr, "Error", "Time period does not specified!");
                return;
            }

            if (sum_per_time == -1) {
                QMessageBox::critical(nullptr, "Error", "Sum per time does not specified");
                return;
            }

            AutomaticTransactionService::getInstance()->createAutomaticTransaction(curr_card.cardId(), card.cardId(), sum, sum_per_time, time_period, 0);

        } else {
            TransactionService::getInstance()->makeTransfer(sum, curr_card.cardId(), card.cardId());
        }

        InitATM(current_card_id);

        ui->screens_container->setCurrentIndex(3);


    }  catch (NotFoundException ex) {
        QMessageBox::critical(nullptr, "Error", "Card number does not exist or does not specified!\n" + QString::number(number));
    }





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
    ui->transaction_widget->setVisible(false);
    ui->screens_container->setCurrentIndex(2);
}


void Widget::on_transfer_button_clicked()
{  
    ui->transfer_card_field->clear();
    ui->sum_field->clear();
    ui->time_period_field->clear();
    ui->sum_per_time_field->clear();
    ui->advanced_mode_check_box->setCheckState(Qt::Unchecked);

    ui->screens_container->setCurrentIndex(5);
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

        //CardEntity card = CardEntity(012, 1111111111111111, 0000, 0, "test", 12342);
        //CardRepositoryVectorImpl::getInstance()->setById(0, card);

        //TransactionEntity tr = TransactionEntity(2, 012, 123, 2222, 1);
        //TransactionRepositoryVectorImpl::getInstance()->setById(2, tr);
        return;
    }

    CardEntity card = CardRepositoryVectorImpl::getInstance()->getByCardId(card_number);
    InitATM(card.id());

    //QMessageBox::information(nullptr, "Info", QString::number(card.cardId()));
    ui->screens_container->setCurrentIndex(3);
}


void Widget::on_cancel_changes_button_clicked()
{
    ui->screens_container->setCurrentIndex(3);
}


void Widget::on_save_changes_button_clicked()
{
    int new_pin = ui->pin_edit_field->GetPin();
    long max_sum = ui->max_sum_field->GetAmount();
    long min_sum = ui->min_sum_field->GetAmount();
    long long reserve_card_number = ui->reserve_card_field->GetCardNumber();
    long long overflow_card_number = ui->overflow_card_field->GetCardNumber();
    int reserve_card_pin = ui->reserve_pin_field->GetPin();
    CardEntity entity = CardRepositoryVectorImpl::getInstance()->getById(current_card_id);


    if (new_pin == -1) {
        QMessageBox::critical(nullptr, "Error", "Pin must contain 4 digits!");
        return;
    }
    entity._pin = new_pin;

    if (max_sum <= min_sum) {
        QMessageBox::critical(nullptr, "Error", "Max sum must be greater then min sum!");
        return;
    }
    entity._max_balance = max_sum;
    entity._min_balance = min_sum;


    if (ui->overflow_card_field->text() != "")
        try {
            //CardService::getInstance()->setAsOverflowCard(entity.cardId(), overflow_card_number, max_sum);
            CardEntity overflow_card = CardRepositoryVectorImpl::getInstance()->getByCardId(overflow_card_number);
            entity._overflow_card_id = new long (overflow_card.id());
        } catch (NotFoundException ex) {
            QMessageBox::warning(nullptr, "Warning", "Reserve card number does not exist!");
        }

    if (ui->reserve_card_field->text() != "")
        try {
            CardEntity reserve_card = CardRepositoryVectorImpl::getInstance()->getByCardId(reserve_card_number);
            if (reserve_card.pin() != reserve_card_pin) {
                QMessageBox::warning(nullptr, "Warning", "Incorrect pin for reserve");
            } else {
                entity._reserve_card_id = new long (reserve_card.id());
            }
        } catch (NotFoundException ex) {
           QMessageBox::warning(nullptr, "Warning", "Reserve card number does not exist!");
        }

    CardRepositoryVectorImpl::getInstance()->setById(current_card_id, entity);
    InitATM(current_card_id);
    ui->screens_container->setCurrentIndex(3);
}


void Widget::on_auto_transactions_button_clicked()
{
    ui->auto_transaction_widget->setVisible(false);
    ui->screens_container->setCurrentIndex(4);
}


void Widget::on_auto_cancel_button_clicked()
{
    ui->screens_container->setCurrentIndex(3);
}


void Widget::on_auto_exit_button_clicked() {
    ui->screens_container->setCurrentIndex(3);
}

void Widget::InitATM(long card_id) {
    current_card_id = card_id;
    CardEntity card = CardRepositoryVectorImpl::getInstance()->getById(current_card_id);
    ui->balance_field_1->SetAmount(card.balance());
    ui->balance_field_2->SetAmount(card.balance());
    ui->pin_edit_field->SetPin(card.pin());
    ui->transaction_list->clear();
    for (TransactionEntity entity : TransactionRepositoryVectorImpl::getInstance()->getAll()) {
        if (entity.fromCardId() == card.id() || entity.toCardId() == card.id()) {
            ui->transaction_list->addItem(new QTransactionItem(entity.id(), card.id()));
        }
    }

    for (AutomaticTransactionEntity entity : AutomaticTransactionRepositoryVectorImpl::getInstance()->getAll()) {
        if (entity.fromCardId() == card.id()) {
            ui->auto_transaction_list->addItem(new QAutoTransactionItem(entity.id(), card.id()));
        }
    }

    ui->max_sum_field->SetAmount(card.maxBalance());
    ui->min_sum_field->SetAmount(card.minBalance());

    if (card.overflowCardId() != nullptr) {
        CardEntity overflow_card = CardRepositoryVectorImpl::getInstance()->getById(*card.overflowCardId());
        ui->overflow_card_field->SetCardNumber(overflow_card.cardId());
    } else {
        ui->overflow_card_field->clear();
    }

    if (card.reserveCardId() != nullptr) {
        CardEntity reserve_card = CardRepositoryVectorImpl::getInstance()->getById(*card.reserveCardId());
        ui->reserve_card_field->SetCardNumber(reserve_card.cardId());
        ui->reserve_pin_field->SetPin(reserve_card.pin());
    } else {
        ui->reserve_card_field->clear();
        ui->reserve_pin_field->clear();
    }
}


void Widget::on_transaction_list_itemClicked(QListWidgetItem *item)
{
    ui->transaction_widget->setVisible(true);
    long transaction_id = static_cast<QTransactionItem*>(item)->transaction_id;
    TransactionEntity transaction = TransactionRepositoryVectorImpl::getInstance()->getById(transaction_id);
    CardEntity from_card = CardRepositoryVectorImpl::getInstance()->getById(transaction.fromCardId());
    CardEntity to_card = CardRepositoryVectorImpl::getInstance()->getById(transaction.toCardId());

    if (transaction.toCardId() == current_card_id) {
        ui->transaction_card_field->SetCardNumber(from_card.cardId());
        ui->role_label->setText("Sender");
    } else {
        ui->transaction_card_field->SetCardNumber(to_card.cardId());
        ui->role_label->setText("Reciever");
    }

    ui->transaction_sum_field->SetAmount(transaction.amount());



}


void Widget::on_auto_transaction_list_itemClicked(QListWidgetItem *item)
{
    ui->auto_transaction_widget->setVisible(true);
    long transaction_id = static_cast<QAutoTransactionItem*>(item)->transaction_id;
    AutomaticTransactionEntity transaction = AutomaticTransactionRepositoryVectorImpl::getInstance()->getById(transaction_id);
    CardEntity from_card = CardRepositoryVectorImpl::getInstance()->getById(transaction.fromCardId());
    CardEntity to_card = CardRepositoryVectorImpl::getInstance()->getById(transaction.toCardId());

    //ui->auto_amount_field->setText("????");
    ui->completed_field->SetAmount(transaction.amount());

    if (transaction.fromCardId() == current_card_id) {
        ui->auto_card_field->SetCardNumber(to_card.cardId());
    } else {
        ui->auto_card_field->SetCardNumber(from_card.cardId());
    }
}

