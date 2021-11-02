#include "view/widget.h"

#include <QApplication>
#include "service/cardservice.h"

int main(int argc, char *argv[])
{
    CardService cs;
    cs.editPin(1234567890123456, 4455, 4444);

    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();


}
