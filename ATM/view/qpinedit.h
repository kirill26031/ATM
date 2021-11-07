#ifndef QPINEDIT_H
#define QPINEDIT_H

#include <QLineEdit>
#include <QKeyEvent>
#include <QString>

class QPinEdit : public QLineEdit
{
public:
    QPinEdit();

    QPinEdit(QWidget *parent = nullptr) : QLineEdit(parent) {}

    virtual void keyPressEvent(QKeyEvent *event) override {

        QString str = text();


        switch (event->key()) {
            case Qt::Key_0: str += "0"; break;
            case Qt::Key_1: str += "1"; break;
            case Qt::Key_2: str += "2"; break;
            case Qt::Key_3: str += "3"; break;
            case Qt::Key_4: str += "4"; break;
            case Qt::Key_5: str += "5"; break;
            case Qt::Key_6: str += "6"; break;
            case Qt::Key_7: str += "7"; break;
            case Qt::Key_8: str += "8"; break;
            case Qt::Key_9: str += "9"; break;
            case Qt::Key_Backspace: {
                if (!str.isEmpty()) str = str.left(str.length()-1);
            }
        }

        if (str.length() > 4) str = str.left(4);

        setText(str);
    }



    int GetPin() {
        QString str = text();

        if (str.length() != 4) return -1;

        bool ok;
        int result = str.toInt(&ok);
        if (ok)
            return result; else
            return -1;
    }

    bool HasPin() {
        return GetPin() != -1;
    }

    void SetPin(int pin) {
        QString str = QString::number(pin);
        while (str.length() < 4) str = "0"+str;
        setText(str);
    }
};

#endif // QPINEDIT_H
