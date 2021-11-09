#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QListWidgetItem>
#include <model/cardentity.h>
#include "service/automatictransactionservice.h"
#include "service/cardservice.h"
#include "service/transactionservice.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_ok_button_clicked();

    void on_cancel_button_clicked();

    void on_advanced_mode_check_box_stateChanged(int arg1);

    void on_exit_button_clicked();

    void on_card_button_clicked();

    void on_transactions_button_clicked();

    void on_transfer_button_clicked();

    void on_transaction_exit_button_clicked();

    void on_init_submit_button_clicked();

    void on_cancel_changes_button_clicked();

    void on_save_changes_button_clicked();

    void on_auto_transactions_button_clicked();

    void on_auto_cancel_button_clicked();

    void on_auto_exit_button_clicked();

    void on_transaction_list_itemClicked(QListWidgetItem *item);

    void on_auto_transaction_list_itemClicked(QListWidgetItem *item);



    void on_screens_container_currentChanged(int arg1);

private:
    long current_card_id = -1;
    CardService* _card_service;
    AutomaticTransactionService* _auto_service;
    TransactionService* _transaction_service;

    Ui::Widget *ui;

    void UpdateATM(long card_id);

};
#endif // WIDGET_H
