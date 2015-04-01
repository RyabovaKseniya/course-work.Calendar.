#include "emailsenddialog.h"
#include "ui_emailsenddialog.h"

EmailSendDialog::EmailSendDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EmailSendDialog)
{
    ui->setupUi(this);
}

EmailSendDialog::~EmailSendDialog()
{
    delete ui;
}
