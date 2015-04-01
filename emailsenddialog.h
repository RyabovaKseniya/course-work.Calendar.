#ifndef EMAILSENDDIALOG_H
#define EMAILSENDDIALOG_H

#include <QDialog>

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
};

#endif // EMAILSENDDIALOG_H
