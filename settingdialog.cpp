#include "settingdialog.h"
#include "ui_settingdialog.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlQuery>
#include <iostream>
#include <QDate>



/**
 * @class SettingDialog
 * @brief В данном классе реализуется окно «Настройки», содержащее 4 вкладки: «Стили», «Языки», «Рассылка», «Уведомление»
 */

SettingDialog::SettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{

    ui->setupUi(this);

    ui->choiceListLanguage->addItem("Русский");
    ui->choiceListLanguage->addItem("English");


    connect(this->ui->okSaveSettingButton, SIGNAL(clicked()), this, SLOT(okSaveSettingButton()));
    connect(this->ui->choiceListLanguage, SIGNAL(activated(QString)), this, SLOT(on_choiceListLanguage_activated(QString)));

}

SettingDialog::~SettingDialog()
{

    delete ui;
}

void SettingDialog::okSaveSettingButton()
{
    close();
}

void SettingDialog::cancelSettingButton()
{
    close();
}


void SettingDialog::applySettingButton()
{
      close();
}

void SettingDialog::on_choiceListLanguage_activated(const QString choiceLanguage)
{
    if (choiceLanguage == "Русский"){
        std::cout << "russian " << std::endl;
        std::cout << translator.load("calendar_eng.qm", ".") << std::endl;
    }
    if (choiceLanguage == "English"){
        std::cout << "english " << std::endl;
        std::cout << translator.load("calendar_ru.qm", ".") << std::endl;
    }
    qApp->installTranslator(&translator);
}



void SettingDialog::changeEvent(QEvent *apcEvt)
{
    std::cout << "event!" << std::endl;
    if(apcEvt->type()==QEvent::LanguageChange)
    {
        std::cout << "LanguageChangeEvent!" << std::endl;

        setWindowTitle(tr("Настройки"));
        ui->tabWidget->setTabText(1, tr("Языки"));
        ui->tabWidget->setTabText(2, tr("Рассылка"));
        ui->tabWidget->setTabText(3, tr("Уведомление"));
        ui->txtLanguageChoice->setText(tr("Выбрать язык:"));
        ui->txtRemainderEmail->setText(tr("Если Вы хотите, чтобы за определенное время вам приходило напоминание о днях рождения ваших друзей и близких на вашу электронную почту, введите, пожалуйста, свой e-mail.Вы можете выбрать из списка несколько e-mail. А также удалить не используемые e-mail."));
        ui->txtAddEmail->setText(tr("Добавить e-mail:"));
        ui->txtReminderPeriod->setText(tr("Напомнить за:"));
        ui->txtTextRemainder->setText(tr("Текст напоминания:"));
        ui->txtAutoload->setText(tr("Показывать при каждом включении компьютера"));
        ui->txtPeriod->setText(tr("Выберете, пожалуйста, за сколько дней до дня рождения показывать уведомление"));

    }
}

void SettingDialog::on_okSaveEmailButton_clicked()
{
    QString email = ui->logField->text();
    DBManager::getInstance()->addRecordToPersonalEmail(email);
    ui->logField->clear();
    fillListOfEmails();

}

void SettingDialog::on_tabWidget_tabBarClicked(int index)
{
    if (index == 1){
        fillListOfEmails();
    }
}

void SettingDialog::fillListOfEmails(){
    ui->emailListWidget->clear();
    QList<QString> list = DBManager::getInstance()->getListOfEmails();
    for (int i=0; i<list.length(); i++){
        ui->emailListWidget->addItem(list.at(i));
        ui->emailListWidget->item(i)->setCheckState(Qt::Checked);
    }
    getCheckedEmails();
}

void SettingDialog::getCheckedEmails(){

    QList<QListWidgetItem*> list = ui->emailListWidget->selectedItems();
    std::cout << list.size() << std::endl;
}

QList<QString> SettingDialog::getBPersons()
{
    QList < QPair < QString, QPair<int, int> > > list;
    list = DBManager::getInstance()->getForNotification(QDate::currentDate().day(), QDate::currentDate().month());
    QList<QString> resList;
    for (int i=0; i<list.size(); i++){
        resList.append(list.at(i).first);
    }
    return resList;
}


