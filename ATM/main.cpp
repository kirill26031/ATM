#include "view/widget.h"
#include <QDebug>
#include <QApplication>
#include "service/cardservice.h"
#include "service/transactionservice.h"
#include "service/automatictransactionservice.h"
#include "repository/db_impl/userrepositorydbimpl.h"
#include <tests/unittests.h>

#define NODEBUG 1

int main(int argc, char *argv[])
{
    if(!NODEBUG)
    {
        UnitTests tests;
        tests.runTests();
    }

    try{

       AutomaticTransactionService* a_t_s = AutomaticTransactionService::getInstance();
       a_t_s->checkAndExecute();

    }
    catch(const CustomException& e)
    {
        qDebug() << e._message.c_str();
    }


    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();


}
