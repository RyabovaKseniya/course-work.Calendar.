#ifndef NOTIFICATIONDIALOG_H
#define NOTIFICATIONDIALOG_H

#include <QDialog>
#include "emailsenddialog.h"
namespace Ui {
class NotificationDialog;
}

class NotificationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NotificationDialog(QWidget *parent = 0);
    ~NotificationDialog();

private slots:
    void on_pushButton_clicked();

private:
    void scanForBirthdayPerson ();
    Ui::NotificationDialog *ui;
};

#endif // NOTIFICATIONDIALOG_H
