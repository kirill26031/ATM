#include "view/widget.h"
#include <QDebug>
#include <QApplication>
#include "service/cardservice.h"

int main(int argc, char *argv[])
{
    CardService* cs = CardService::getInstance();
    try {
        cs->editPin(1234567890123456, 4355, 4444);
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
