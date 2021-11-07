#ifndef QAMOUNTEDIT_H
#define QAMOUNTEDIT_H

#include <QLineEdit>
#include <QKeyEvent>

class QAmountEdit : public QLineEdit
{
public:
    QAmountEdit();

    QAmountEdit(QWidget *parent = nullptr) : QLineEdit(parent) {}

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
            case Qt::Key_Comma: {
                if (str.contains('.')) break;
                if (str.length() == 0) break;
                str += ".";
                break;
            }
            case Qt::Key_Backspace: {
                if (!str.isEmpty()) str = str.left(str.length()-1);
            }
        }
        int idx = str.indexOf('.');
        if (idx != -1 && idx + 2 < str.length())
            str = str.left(idx + 3);


        setText(str);
    }



    long GetAmount() {
        QString str = text();
        if (!str.contains('.')) str += '.';
        int idx = str.indexOf('.');
        while (str.length() <= idx + 2) str += '0';
        str.remove('.');

        bool ok;
        long result = str.toLong(&ok);
        if (ok)
            return result; else
            return -1;
    }


    void SetAmount(long amount) {
        setText(Amount(amount));
    }

    static QString Amount(long amount){
        QString str = QString::number(amount);
        while (str.length() < 3) str = "0"+str;
        str = str.left(str.length()-2) + "." + str.right(2);
        if (str[str.length()-1] == '0') str = str.left(str.length()-1);
        return str;
    }
};

#endif // QAMOUNTEDIT_H
