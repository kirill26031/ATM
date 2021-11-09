#include "view/widget.h"
#include <QDebug>
#include <QApplication>
#include "service/cardservice.h"
#include "service/transactionservice.h"
#include "service/automatictransactionservice.h"
#include "repository/db_impl/userrepositorydbimpl.h"
#include <tests/unittests.h>
#include <config.h>

int main(int argc, char *argv[])
{
    if(Config::DEBUG_MODE)
    {
        UnitTests tests;
        tests.runTests();
    }


    try{
    QApplication a(argc, argv);
    Widget w;

    try{

       AutomaticTransactionService* a_t_s = AutomaticTransactionService::getInstance();
       a_t_s->checkAndExecute();

    }
    catch(const CustomException& e)
    {
        qDebug() << e._message.c_str();
    }

    w.show();
    int res = a.exec();
    return res;
    }
    catch(const CustomException& e)
    {
        qDebug() << e._message.c_str();
    }



}
