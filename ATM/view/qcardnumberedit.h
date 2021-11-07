#ifndef QCARDNUMBEREDIT_H
#define QCARDNUMBEREDIT_H

#include <QLineEdit>
#include <QKeyEvent>

class QCardNumberEdit : public QLineEdit
{
public:
    QCardNumberEdit(QWidget *parent = nullptr) : QLineEdit(parent) {}

    virtual void keyPressEvent(QKeyEvent *event) override {

        QString str = text();
        if (str.length() == 4 || str.length() == 9 || str.length() == 14) str += "-";

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
                if (!str.isEmpty() && str.back() == '-') str = str.left(str.length()-1);
                if (!str.isEmpty()) str = str.left(str.length()-1);
            }
        }

        if (!str.isEmpty() && str.back() == '-') str = str.left(str.length()-1);
        if (str.length() > 19) str = str.left(19);

        setText(str);
    }



    long long GetCardNumber() {
        QString str = text().remove('-');

        if (str.length() != 16) return -1;

        bool ok;
        long long result = str.toLongLong(&ok);
        if (ok)
            return result; else
            return -1;
    }

    bool HasCardNumber() {
        return GetCardNumber() != -1;
    }

    void SetCardNumber(long long number) {        
        setText(CardNumber(number));
    }

    static QString CardNumber(long long number){
        QString str = QString::number(number);
        while (str.length() < 16) str = "0"+str;
        str = str.mid(0, 4) + "-" + str.mid(4, 4) + "-"+str.mid(8, 4) + "-" + str.mid(12, 4);
        return str;
    }

    static QString ShortCardNumber(long long number){
        return CardNumber(number).left(9);
    }
};

#endif // QCARDNUMBEREDIT_H
