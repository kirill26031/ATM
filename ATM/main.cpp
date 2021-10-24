#include "view/widget.h"

#include <QApplication>
#include "service/cardservice.h"

int main(int argc, char *argv[])
{
    CardService cs;
    cs.editPin({1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6}, {4, 4, 5, 5}, {4, 4, 4, 4});

    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
