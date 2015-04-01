#include "notificationdialog.h"
#include "ui_notificationdialog.h"
#include <QDesktopWidget>
#include <QApplication>

NotificationDialog::NotificationDialog(QWidget *parent) :
    QDialog(NULL),
    ui(new Ui::NotificationDialog)
{
    ui->setupUi(this);
    setWindowOpacity(0.3);
    setWindowFlags(Qt::FramelessWindowHint);
    QDesktopWidget* desktop = QApplication::desktop();
    move(desktop->screenGeometry().bottomRight().x() - width(), desktop->screenGeometry().bottomRight().y()-height()-38);


}




NotificationDialog::~NotificationDialog()
{
    delete ui;
}
