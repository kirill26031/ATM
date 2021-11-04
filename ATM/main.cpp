#include "view/widget.h"
#include <QDebug>
#include <QApplication>
#include "service/cardservice.h"

int main(int argc, char *argv[])
{
    CardService* cs = CardService::getInstance();
    try {
//        cs->editPin(1234567890123456, 4355, 4444);
        // 9012345612345678
//        long new_id = cs->generateCard(0, std::string("Card new"));
//        bool exists = cs->cardIdExists(new_id);
//        const CardEntity& card = cs->getCardById(new_id);
//        bool correct = cs->areCardCredentialsCorrect(new_id, card.pin());
//        qDebug() << exists << " " << correct;
//    cs->setAsReserveCard(9012345612345678, 1234567890123456, 200);
//    const CardEntity& protected_card = cs->getCardById(1);
//    const CardEntity& reserve_card = cs->getCardById(0);
//      cs->setAsOverflowCard(9012345612345678, 1234567890123456, 200);
//      const CardEntity& overflow_source = cs->getCardById(1);
//      const CardEntity& overflow_target = cs->getCardById(0);
    int x = 2+ 3;
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
