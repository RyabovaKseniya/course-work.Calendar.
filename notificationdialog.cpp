#include "notificationdialog.h"
#include "ui_notificationdialog.h"
#include <QDesktopWidget>
#include <QApplication>
#include <dbmanager.h>
#include <QDate>

NotificationDialog::NotificationDialog(QWidget *parent) :
    QDialog(NULL),
    ui(new Ui::NotificationDialog)
{
    ui->setupUi(this);

    connect(this->ui->closeButton, SIGNAL(clicked()), this, SLOT(close()));

    QPalette palette = QWidget::palette();
    QPixmap background = QPixmap(":/resources/images.jpg");
    QBrush brush(background);
    palette.setBrush(QPalette::Active,QPalette::Background, brush);
    palette.setBrush(QPalette::Inactive,QPalette::Background, brush);
    setPalette(palette);

    setWindowOpacity(0.85);
    setWindowFlags(Qt::FramelessWindowHint | Qt::BypassGraphicsProxyWidget);
    QDesktopWidget* desktop = QApplication::desktop();
    move(desktop->screenGeometry().bottomRight().x() - width(), desktop->screenGeometry().bottomRight().y()-height()-38);
    scanForBirthdayPerson();
}


NotificationDialog::~NotificationDialog()
{
    delete ui;
}

void NotificationDialog:: scanForBirthdayPerson (){

    QList < QPair < QString, QPair<int, int> > > list;
    list = DBManager::getInstance()->getForNotification(QDate::currentDate().day(), QDate::currentDate().month());
    if (list.isEmpty()){
        ui->label->setText(tr("Сегодня никто не празднует День Рождения ;("));
        return;
    }
    for (int i=0; i< list.size(); i++){
        QPair<QString, QPair<int, int > > item =  list.at(i);
        QPair<int, int > pairYearAndId = item.second;
        int year = pairYearAndId.first;
        ui->label->setText(ui->label->text() +"\n"+ tr("Сегодня %1 празднует свой День Рождения. Исполняется %2").arg(item.first).arg(year));
    }
}


void NotificationDialog::on_pushButton_clicked()
{
    EmailSendDialog* esd = new EmailSendDialog();
    esd->show();
}


