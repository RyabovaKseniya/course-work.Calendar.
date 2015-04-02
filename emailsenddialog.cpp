#include "emailsenddialog.h"
#include "ui_emailsenddialog.h"
#include "iostream"
#include <QMessageBox>
#include <smtp.h>

EmailSendDialog::EmailSendDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EmailSendDialog)
{
    ui->setupUi(this);
    connect(this->ui->choicePattern, SIGNAL(currentIndexChanged(int)), this, SLOT(getCongratulationText(int)));
    connect (ui->choiceListBirthdayPersons, SIGNAL(currentTextChanged(QString)), this, SLOT (getEmailFromDB(QString)));
    connect(ui->sendButton, SIGNAL(clicked()), this, SLOT(sendCongratulation()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(close()));
    fillChoiceListOfCongratulation();
    fillChoiceListBPersons();
    getEmailFromDB(ui->choiceListBirthdayPersons->currentText());
}

void EmailSendDialog::changeEvent(QEvent *apcEvt)
{
    if(apcEvt->type()==QEvent::LanguageChange)
    {
        setWindowTitle(tr("Отправка поздравлений"));
        ui->txtFrom->setText(tr("ОТ КОГО:"));
        ui->txtSubject->setText(tr("Тема:"));
        ui->txtTo->setText(tr("КОМУ:"));
        ui->txtPattern->setText(tr("Вы можете использовать в качестве поздравления один из стандартных шаблонов. А также написать свое поздравление."));
        ui->cancelButton->setText(tr("Отмена"));
    }
}

void EmailSendDialog::getCongratulationText(const int arg1)
{
    /// get congratulation text for differnt group of people
    QString q = DBManager::getInstance()->getTextFor(arg1);
    ui->congratulationText->setText(q);
}

void EmailSendDialog::fillChoiceListOfCongratulation()
{
    // получить модель для combobox
    ui->choicePattern->setModel(DBManager::getInstance()->listTextCongr());
    // получить тексты
    getCongratulationText(0);
}


EmailSendDialog::~EmailSendDialog()
{
    delete ui;
}


void EmailSendDialog::sendCongratulation()
{
    if (ui->recipienEmailtField->text() == ""){
        QMessageBox::information(this, tr("Ошибка"), tr("Поле email пусто!"));
        return;
    }
    Smtp* smtp = new Smtp("congratulation.delivery@mail.ru", "Congratulation94", "smtp.mail.ru", 465);
    smtp->sendMail("congratulation.delivery@mail.ru", ui->recipienEmailtField->text() , ui->subjectField->text(), ui->congratulationText->toPlainText());
}


void EmailSendDialog::getEmailFromDB(QString name)
{
    std:: cout << "getEmailFromDB "<< std::endl;
    int id = mapOfBirthdayPersons.value(name);
    QString email = DBManager::getInstance()->email(id);
    ui->recipienEmailtField->setText(email);
}

void EmailSendDialog::fillChoiceListBPersons()
{
    ui->choiceListBirthdayPersons->clear();
    mapOfBirthdayPersons.clear();
    QList < QPair < QString, QPair<int, int> > > list;
    list = DBManager::getInstance()->getForNotification(QDate::currentDate().day(), QDate::currentDate().month());
    for (int i=0; i<list.size(); i++){
        ui->choiceListBirthdayPersons->addItem(list.at(i).first);

        QPair < QString, QPair < int, int > > pairNameAndPair = list.at(i);
        QString name = pairNameAndPair.first;
        int id = pairNameAndPair.second.second;
        mapOfBirthdayPersons.insert(name, id);
    }
}

