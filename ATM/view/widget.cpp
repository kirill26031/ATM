#include "widget.h"
#include "./ui_widget.h"

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

