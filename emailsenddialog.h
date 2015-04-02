#ifndef EMAILSENDDIALOG_H
#define EMAILSENDDIALOG_H

#include <QDialog>
#include <dbmanager.h>
#include <QDate>

namespace Ui {
class EmailSendDialog;
}

class EmailSendDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EmailSendDialog(QWidget *parent = 0);
    ~EmailSendDialog();

private:
    Ui::EmailSendDialog *ui;
    QMap <QString, int> mapOfBirthdayPersons;
private slots:

    void getCongratulationText(int arg1);

    void fillChoiceListOfCongratulation();

    void fillChoiceListBPersons();

    void getEmailFromDB(QString name);

    void sendCongratulation();



protected:
    void changeEvent(QEvent *apcEvt);
};

#endif // EMAILSENDDIALOG_H
