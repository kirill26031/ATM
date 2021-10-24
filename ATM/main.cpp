#include "view/widget.h"

#include <QApplication>
#include "service/cardservice.h"

int main(int argc, char *argv[])
{
    CardService cs;
    cs.editPin(std::array<int, 16>(), std::array<int, 4>(), std::array<int, 4>());

    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
