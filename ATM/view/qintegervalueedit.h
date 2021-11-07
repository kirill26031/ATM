#ifndef QINTEGERVALUEEDIT_H
#define QINTEGERVALUEEDIT_H

#include <QLineEdit>
#include <QKeyEvent>
#include <QString>

class QIntegerValueEdit : public QLineEdit
{
public:

    QIntegerValueEdit(QWidget *parent = nullptr) : QLineEdit(parent) {}

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

        setText(str);
    }



    long long GetInteger() {
        QString str = text();

        bool ok;
        long long result = str.toLongLong(&ok);
        if (ok)
            return result; else
            return -1;
    }

    bool HasInteger() {
        return GetInteger() != -1;
    }

    void SetInteger(long long value) {
        setText(QString::number(value));
    }
};

#endif // QINTEGERVALUEEDIT_H
